const sql = require('sql-easy-lib');
const database = require('../database/db-conn');
const crypt = require('../cryptography/main-module');

function getMessagesMD5 () {
	const myselfId = database.get('envs', new sql.Request([{
		key : 'authedAccount'
	}]))[0].value;
	if (!myselfId) {
		return "not-authed";
	}
	
	return crypt.md5(JSON.stringify(
		database.get('messages', new sql.Request([{
			ownerId : myselfId
		}]))
	));
}

try {
	process.stdout.write(getMessagesMD5());
}
catch (e) {
	process.stdout.write(e.message);
	// process.stdout.write("\n" + e.stack);
}