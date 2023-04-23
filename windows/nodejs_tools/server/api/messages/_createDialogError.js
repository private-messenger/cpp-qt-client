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


class DeleteChat extends njsbacker.Method {
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
		
		database.remove('messages', new sql.Request([{
			chatId : params.id
		}]));
		
		return "ok";
	}
}

module.exports = new DeleteChat('messages.createDialogError', '/messages.createDialogError', {
	id : {
		required      : true,
		type          : njsbacker.types.string,
		conversion    : false,
		// allow_methods : ['post']
		allow_methods : ['get', 'post']
	}
});