const sql = require('sql-easy-lib');
//const database = new sql.SQLite3_database('../../appdata');

if (!process.argv[2] && !process.argv.slice(3).join(' ')) {
	process.stdout.write('');
}
else {
	try {
		const database = require('./db-conn');
		database.set('envs',
			new sql.Request([{
				key : process.argv[2]
			}]),
			{
				value : process.argv.slice(3).join(' ')
			}
		);

		process.stdout.write("ok");
	}
	catch (e) {
		process.stdout.write(e.message);
	}
}

