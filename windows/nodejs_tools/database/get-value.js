const sql = require('sql-easy-lib');
//const fs = require('fs');
const database = require('./db-conn');
//const crypt = require('../cryptography/main-module');

function getValue ( key ) {
	if (!key) {
		return "missing key";
	}
	let value = database.get('envs', new sql.Request([{
		key
	}]))[0].value;
	if (!value) {
		return "undefined key";
	}
	else {
		return value;
	}
}

try {
	process.stdout.write(getValue(process.argv[2]));
}
catch (e) {
	process.stdout.write(e.message);
}