const sql = require('sql-easy-lib');
//const fs = require('fs');
const database = require('./db-conn');

try {
	var myselfId = database.get('envs', new sql.Request([{
		key : 'authedAccount'
	}]))[0].value;

	if (!myselfId) {
		process.stdout.write("not-authed");
	}
	else {
		var users = database.get('users', null, 'id, login');
		
		var contacts = database.get('`contact-book`', new sql.Request([{
			ownerId : myselfId
		}])).map(item => {
			item.login = sql.tools.get_from_key(users, new sql.Request([{
				id : item.contactId
			}]))[0].login;
			
			// return item;
			return `${item.login}:${item.contactId}`;
		}).join("|");
		
		process.stdout.write(contacts == "" ? "null" : contacts);
	}
}
catch (e) {
	process.stdout.write(e.message);
	// process.stdout.write(e.stack);
}