const sql = require('sql-easy-lib');

function logoutNowFunct (database) {
	database.set('envs', new sql.Request([{
		key   : 'authedAccount'
	}, {
		key   : 'activeKey'
	}]), {
		value : null
	});
	
	process.stdout.write("ok");
}

try {
	logoutNowFunct(
		require('./db-conn')
	);
}
catch (e) {
	process.stdout.write(e.message);
}