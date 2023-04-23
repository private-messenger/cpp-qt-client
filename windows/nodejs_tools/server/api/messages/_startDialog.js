const njsbacker = require('njsbacker');
const sql = require('sql-easy-lib');
const connectDb = () => require('../../../database/db-conn');
const { int16bit, usertype } = require('../types');
const crypt = require('../../../cryptography/main-module');
const request = require('request-promise');


const randint = (min, max) => Math.floor(Math.random() * (max - min + 1) + min);


function generateChatId (database) {
	const alphabet = "1234567890abcdef";
	let generatedId = "";
	for (let i=0; i < 64; i++) {
		generatedId += alphabet[randint(0, 15)];
	}
	return generatedId;
	/*if (!database.get('messages', new sql.Request([{
		chatId : generatedId
	}]))[0]) {
		return generatedId;
	}
	else {
		return generateChatId(database);
	}*/
}


class CreateChat extends njsbacker.Method {
	async execute (params, session, groups) {
		const database = connectDb();
		
		// (!) В дальнейших апдейтах - переписать в виду того, что может измениться порядок записи в БД.
		const userData = database.get('envs', new sql.Request([{
			key : 'authedAccount'
		}, {
			key : 'activeKey'
		}, {
			key : 'i2pPortHttp'
		}], 'value'));
		if (!userData[0] || !userData[1]) {
			throw new njsbacker.ApiError("UNAUTHORIZED_ACCESS", {
				warning : "Database contains errors, please, reinstall program."
			});
		}
		const userKey = Buffer.from(userData[0].value);
		const userId  = userData[1].value;
		const i2pPort = userData[2].value;
		
		if (!userId || !userKey) {
			throw new njsbacker.ApiError("UNAUTHORIZED_ACCESS", {});
		}
		
		const userObject = database.get('users', new sql.Request([{
			id : userId
		}]))[0];
		if (!userObject) {
			throw new njsbacker.ApiError("UNAUTHORIZED_ACCESS", {});
		}
		else if (!database.get('`contact-book`', new sql.Request([{
			ownerId   : userId,
			contactId : params.to_id
		}]))[0]) {
			throw new njsbacker.ApiError("UNDEFINED_USER", {});
		}
		
		const recipientObject = database.get('users', new sql.Request([{
			id : params.to_id
		}]))[0];
		
		const chatCryptor = crypt.generateAES();
		const userCryptor = new crypt.AES(
			new crypt.CryptKey(userKey)
		);
		const publicKey  = userObject.publickey;
		const privateKey = userCryptor.decrypt(Buffer.from(userObject.privkey_encoded));
		
		const rsaCryptorRecipient = new crypt.Crypt({
			public_key  :  new crypt.CryptKey(Buffer.from(recipientObject.publickey))
		});
		
		const chatId = generateChatId(database);
		// console.log("chatId:", chatId);
		
		const i2pProxy   = request.defaults({ proxy : `http://127.0.0.1:${i2pPort}` });
		const md5Msg     = crypt.md5(params.message);
		let resultJSON;
		const encodedChatKey = rsaCryptorRecipient.encrypt(chatCryptor.key.bytes.toString('base64'));
		
		const httpReqUrl = `http://${recipientObject['b32-i2pAddress']}/api/v1/messages.createDialog`;
		
		try {
			const result     = await i2pProxy.get({
				url : httpReqUrl,
				qs  : {
					chat_id  : chatId,
					from     : userId,
				//	^-- (!) Вот тут уязвимость, необходимо её будет устранить в следующих версиях программы, поскольку есть риск подделки запроса.
				//	Для нужд авторизации появится в дальнейшем secret_id, который будет передаваться при первом "заносе" пользователя в списки контактов. Это существенно повысит безопасность пользователей и защитит их от CSRF-атаки (Межсайтовая подделка запроса)
					chat_key : encodedChatKey.toString('base64'),
					message  : Buffer.from(chatCryptor.encrypt(Buffer.from(params.message))).toString('base64')
				}
			});
			resultJSON = JSON.parse(result);
		}
		catch (i2pErr) {
			// console.log(i2pErr);
			if (i2pErr.name == "StatusCodeError") {
				if (i2pErr.statusCode == 400) {
					resultJSON = JSON.parse(i2pErr.error);
				}
				else {
					throw new njsbacker.ApiError("USER_OFFLINE_OR_INVALID", {});
				}
			}
			else {
				throw new njsbacker.ApiError("USER_OFFLINE_OR_INVALID", {});
			}
		}
		if (!resultJSON) {
			throw new njsbacker.ApiError("USER_OFFLINE_OR_INVALID", {});
		}
		else if (!!resultJSON.error) {
			throw new njsbacker.ApiError("REQUEST_RETURN_ERROR", {
				message : resultJSON.error.code,
				details : resultJSON.error.details
			});
		}
		else if (resultJSON.result.md5 != md5Msg) {
			i2pProxy.get(`http://${recipientObject['b32-i2pAddress']}/api/v1/messages.createDialogError?id=${resultJSON.result.id}`);
			throw new njsbacker.ApiError("INVALID_MD5_IN_USER", {
				required : md5Msg,
				returned : resultJSON.result.md5
			});
		}
		database.add('messages', [{
			row             : database.getIndex ('messages', 'row'),
			chatId          : chatId,
			// recipientChatId : resultJSON.result.id,
			ownerId         : userId,
			chatName        : `Chat of ${recipientObject.login}`,
			fromId          : userId,
			toId            : params.to_id,
			message         : Buffer.from(chatCryptor.encrypt(Buffer.from(params.message))),
			messageDate     : Math.round((new Date).getTime() / 1000),
			key             : Buffer.from(userCryptor.encrypt(chatCryptor.key.bytes))
		}]);
		return "ok";
	}
}

module.exports = new CreateChat('messages.startDialog', '/messages.startDialog', {
	to_id : {
		required      : true,
		type          : usertype,
		conversion    : false,
		// allow_methods : ['post']
		allow_methods : ['get', 'post']
	},
	message : {
		required      : true,
		type          : njsbacker.types.string,
		conversion    : false,
		// allow_methods : ['post']
		allow_methods : ['get', 'post']
	}
});