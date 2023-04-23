const sql = require('sql-easy-lib');
//const fs = require('fs');
const database = require('./db-conn');
//const crypt = require('../cryptography/main-module');

function getLoginAndId () {
	let myselfId = database.get('envs', new sql.Request([{
		key : 'authedAccount'
	}]))[0].value;
	if (!myselfId) {
		return "not-authed";
	}
	
	return database.get('users', new sql.Request([{
		id : myselfId
	}]), '`b32-i2pAddress`').map(i => i['b32-i2pAddress'])[0];
}

try {
	process.stdout.write(getLoginAndId());
}
catch (e) {
	process.stdout.write(e.message);
}