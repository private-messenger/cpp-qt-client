//const sql = require('sql-easy-lib');
//const database = new sql.SQLite3_database('../../appdata');
try {
	const database = require('./db-conn');
	database.get('envs');

	process.stdout.write("ok");
}
catch (e) {
	process.stdout.write(e.message);
}