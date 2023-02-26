const sql = require('sql-easy-lib');

try {
	const database = require('./db-conn');
	const authId = database.get('envs', new sql.Request([{
		key : 'authedAccount'
	}]))[0].value;

	process.stdout.write(
		!!authId && database.get('users', new sql.Request([{
			id : authId
		}]))[0] ?
		"1" : "0"
	);
}
catch (e) {
	process.stdout.write(e.message);
}