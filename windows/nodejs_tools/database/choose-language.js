const sql = require('sql-easy-lib');
const fs = require('fs');
const crypt = require('../cryptography/main-module');

function chooseLangFunct (language, database) {
	database.set('envs', new sql.Request([{
		key   : 'activeLang'
	}]), {
		value : language
	});
	process.stdout.write('ok');
}

if (!process.argv[2]) {
	process.stdout.write('failed');
}
else {
	try {
		chooseLangFunct(
			process.argv[2],
			require('./db-conn')
		);
	}
	catch (e) {
		process.stdout.write(e.message);
	}
}