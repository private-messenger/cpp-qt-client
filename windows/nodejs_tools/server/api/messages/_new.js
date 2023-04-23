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


class NewMessage extends njsbacker.Method {
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
		
		const chatObject = database.get('messages', new sql.Request([{
			chatId : params.to_chat
		}]));
		if (chatObject.length == 0) {
			throw new njsbacker.ApiError("UNKNOWN_CHAT_ID", {});
		}
		// Новое сообщение тут
		const userCryptor = new crypt.AES(
			new crypt.CryptKey(userKey)
		);
		const decryptedChatKey = userCryptor.decrypt(chatObject[0].key, false);
		const chatCryptor = new crypt.AES(
			new crypt.CryptKey(
				decryptedChatKey
			)
		);
		const recipientObject = database.get('users', new sql.Request([{
			id : chatObject[0].fromId != userId ? chatObject[0].fromId : chatObject[0].toId
		}]))[0];
		if (!recipientObject) {
			throw new njsbacker.ApiError("UNDEFINED_USER", {});
		}
		
		let saveToMemory = true;
		let message = params.message;
		let resultJSON;
		// Отправим сообщение 
		if (params.to_sender != 1) {
			const i2pProxy = request.defaults({ proxy : `http://127.0.0.1:${i2pPort}` });
			const httpReqUrl = `http://${recipientObject['b32-i2pAddress']}/api/v1/messages.new`;
			try {
				const result     = await i2pProxy.get({
					url : httpReqUrl,
					qs  : {
						to_sender : 1,
						to_chat   : params.to_chat,
						message   : chatCryptor.encrypt(message).toString('base64'),
					}
				});
				resultJSON = JSON.parse(result);
				if (!resultJSON.result) {
					throw new njsbacker.ApiError("REMOTE_SERVER_RETURN_ERROR", { code : resultJSON.error.code, details : resultJSON.error.details });
				}
			}
			catch (i2pErr) {
				saveToMemory = false;
				if (i2pErr.name == "StatusCodeError") {
					if (i2pErr.statusCode == 400) {
						resultJSON = JSON.parse(i2pErr.error);
						throw new njsbacker.ApiError("REMOTE_SERVER_RETURN_ERROR", { code : resultJSON.error.code, details : resultJSON.error.details });
					}
					else {
						throw new njsbacker.ApiError("USER_OFFLINE_OR_INVALID", {});
					}
				}
				else {
					throw new njsbacker.ApiError("USER_OFFLINE_OR_INVALID", {});
				}
			}
		}
		// Сохраним сообщение
		else {
			message = chatCryptor.decrypt(Buffer.from(params.message, 'base64'), false);
		}
		if (saveToMemory) {
			const clientId = chatObject[0].fromId != userId ? chatObject[0].fromId : chatObject[0].toId;
			database.add('messages', [{
				row             : database.getIndex ('messages', 'row'),
				chatId          : params.to_chat,
				ownerId         : userId,
				chatName        : `Chat of ${recipientObject.login}`,
				fromId          : params.to_sender == 1 ? clientId : userId,
				toId            : params.to_sender == 1 ? userId   : clientId,
				message         : Buffer.from(chatCryptor.encrypt(message)),
				messageDate     : Math.round((new Date).getTime() / 1000),
				key             : Buffer.from(userCryptor.encrypt(chatCryptor.key.bytes))
			}]);
		}
		
		return "ok";
	}
}

module.exports = new NewMessage('messages.new', '/messages.new', {
	to_sender : {
		required      : false,
		type          : njsbacker.types.integer,
		conversion    : false,
		// allow_methods : ['post']
		allow_methods : ['get', 'post']
	},
	to_chat : {
		required      : true,
		type          : njsbacker.types.string,
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