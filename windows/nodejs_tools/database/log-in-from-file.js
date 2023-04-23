const sql = require('sql-easy-lib');
const database = require('../database/db-conn');
const crypt = require('../cryptography/main-module');
const fs = require('fs');

function fileRead (path) {
	try {
		return JSON.parse(fs.readFileSync(path, {
			encoding: "utf-8"
		}).toString("utf-8"));
	}
	catch (e) {
		return undefined;
	}
}

function logInFromFile (path) {
	const userData = fileRead(path);
	if (!userData) {
		return "file-not-readed";
	}
	// console.log('userData is', userData);
	if (!database.get('users', new sql.Request([{
		id : userData.id
	}]))[0]) {
		database.add('users', [{
			id                   : userData.id,
			login                : userData.login,
			password_key_encoded : Buffer.from(userData.password_key_encoded, 'base64'),
			publickey            : Buffer.from(userData.publickey, 'base64'),
			privkey_encoded      : Buffer.from(userData.privkey_encoded, 'base64'),
			i2pkey_encoded       : Buffer.from(userData.i2pkey_encoded, 'base64'),
			'`b32-i2pAddress`'   : userData['b32-i2pAddress'],
			storagekey_encoded   : Buffer.from(userData.storagekey_encoded, 'base64'),
			isMyself             : userData.isMyself,
			updateTime           : userData.updateTime,
			storagedAccount      : userData.storagedAccount
		}]);
	}
	database.set('envs', new sql.Request([{
		key   : 'authedAccount'
	}]), {
		value : userData.id
	});
	
	database.set('envs', new sql.Request([{
		key   : 'activeKey'
	}]), {
		value : userData.key
	});
	
	fs.writeFileSync('./application.dat', Buffer.from(userData.i2pkey, 'base64').toString(), {
		encoding : "binary",
		flag     : "w+"
	});
	
	return "ok";
}

try {
	process.stdout.write(logInFromFile(process.argv.slice(2).join(' ')));
}
catch (e) {
	process.stdout.write(e.message);
	process.stdout.write(e.stack);
}