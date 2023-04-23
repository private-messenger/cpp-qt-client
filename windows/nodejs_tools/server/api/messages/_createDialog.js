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
			contactId : params.from
		}]))[0]) {
			throw new njsbacker.ApiError("UNDEFINED_USER", {});
		}
		
		const recipientObject = database.get('users', new sql.Request([{
			id : params.from,
			//secret_id : params.secret_id
		}]))[0];
		/*
		if (!recipientObject) {
			throw new njsbacker.ApiError("CSRF_ATACK_DEFENSE_ERROR", {
				"warning" : "At new version you MUST give secret_id in request. If you show this error, please, enter the address in the contact list again."
			});
		}
		*/
		const userCryptor = new crypt.AES(
			new crypt.CryptKey(userKey)
		);
		
		const publicKey  = userObject.publickey;
		const privateKey = userCryptor.decrypt(Buffer.from(userObject.privkey_encoded));
		
		const rsaCryptorSender = new crypt.Crypt({
			private_key : new crypt.CryptKey(Buffer.from(privateKey)),
			public_key  : new crypt.CryptKey(Buffer.from(publicKey))
		});
		
		const decryptedChatKey = rsaCryptorSender.decrypt(Buffer.from(params.chat_key, 'base64'));
		
		const chatCryptor = new crypt.AES(
			new crypt.CryptKey(
				Buffer.from(decryptedChatKey, 'base64')
			)
		);
		
		const decryptedMessage = chatCryptor.decrypt(Buffer.from(params.message, 'base64')).toString();
		const chatId = generateChatId(database);
		
		database.add('messages', [{
			row             : database.getIndex('messages', 'row'),
			// chatId          : chatId,
			// recipientChatId : params.chat_id,
			ownerId         : userId,
			chatId          : params.chat_id,
			chatName        : `Chat of ${recipientObject.login}`,
			fromId          : params.from,
			toId            : userId,
			message         : Buffer.from(params.message, 'base64'),
			messageDate     : Math.round((new Date).getTime() / 1000),
			key             : userCryptor.encrypt(chatCryptor.key.bytes)
		}]);
		
		return {
			id  : chatId,
			md5 : crypt.md5(decryptedMessage)
		};
	}
}

module.exports = new CreateChat('messages.createDialog', '/messages.createDialog', {
	chat_key : {
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
	},
	from : {
		required      : true,
		type          : usertype,
		conversion    : false,
		// allow_methods : ['post']
		allow_methods : ['get', 'post']
	},
	chat_id : {
		required      : true,
		type          : njsbacker.types.string,
		conversion    : false,
		// allow_methods : ['post']
		allow_methods : ['get', 'post']
	},
	secret_id : {
		required      : false,
		type          : njsbacker.types.string,
		conversion    : false,
		// allow_methods : ['post']
		allow_methods : []
	}
});