const sql = require('sql-easy-lib');
const database = require('../database/db-conn');
const crypt = require('../cryptography/main-module');
const fs = require('fs');

function save (path) {
	const myselfId = database.get('envs', new sql.Request([{
		key : 'authedAccount'
	}]))[0].value;
	if (!myselfId) {
		return "not-authed";
	}
	
	const userObject = database.get('users', new sql.Request([{
		id : myselfId
	}]))[0];
	const userKey = database.get('envs', new sql.Request([{
		key : 'activeKey'
	}]))[0].value;
	
	const cryptKey = new crypt.CryptKey(
		Buffer.from(userKey)
	);
	
	const cryptor = new crypt.AES(cryptKey);
	
	fs.writeFileSync(path, JSON.stringify({
		id                   : userObject.id,
		login                : userObject.login,
		key                  : userKey,
		i2pkey               : Buffer.from(cryptor.decrypt(userObject.i2pkey_encoded)).toString('base64'),
		password_key_encoded : userObject.password_key_encoded.toString('base64'),
		publickey            : userObject.publickey.toString('base64'),
		privkey_encoded      : userObject.privkey_encoded.toString('base64'),
		i2pkey_encoded       : userObject.i2pkey_encoded.toString('base64'),
		'b32-i2pAddress'     : userObject['b32-i2pAddress'],
		storagekey_encoded   : userObject.storagekey_encoded.toString('base64'),
		isMyself             : userObject.isMyself,
		updateTime           : userObject.updateTime,
		storagedAccount      : userObject.storagedAccount
	}), {
		encoding : "utf-8"
	});
	
	return "ok";
}

try {
	process.stdout.write(save(process.argv.slice(2).join(' ')));
}
catch (e) {
	process.stdout.write(e.message);
}