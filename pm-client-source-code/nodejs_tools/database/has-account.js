const sql = require('sql-easy-lib');

if (!process.argv[2]) {
	process.stdout.write('');
}
else {
	try {
		const database = require('./db-conn');
		
		process.stdout.write(!database.get('users', new sql.Request([ { id : process.argv[2] } ]))[0] ? "0" : "1");
	}
	catch (e) {
		process.stdout.write(e.message);
	}
}