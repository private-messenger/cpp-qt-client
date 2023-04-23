const sql = require('sql-easy-lib');
const database = require('./db-conn');

function removeContact (userId) {
	const myselfId = database.get('envs', new sql.Request([{
		key : 'authedAccount'
	}]))[0].value;
	if (!myselfId) {
		return "not-authed";
	}
	
	database.remove('`contact-book`', new sql.Request([{
		ownerId   : myselfId,
		contactId : userId
	}]));
	
	database.remove('messages', new sql.Request([{
		ownerId   : myselfId,
		fromId    : userId
	}, {
		ownerId   : myselfId,
		toId      : userId
	}]));
}

try {
	process.stdout.write(removeContact(process.argv[2]));
}
catch (e) {
	process.stdout.write(e.message);
}