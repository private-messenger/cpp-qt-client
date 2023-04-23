const sql = require('sql-easy-lib');
const fs = require('fs');
const crypt = require('../cryptography/main-module');

function logInFunct (logInData, db, _keyMd5, _cryptor) {
	if (!logInData) {
		return "failed";
	}
	else {
		db.set('envs', new sql.Request([{
			key   : 'authedAccount'
		}]), {
			value : logInData.id
		});
		
		db.set('envs', new sql.Request([{
			key   : 'activeKey'
		}]), {
			value : _keyMd5
		});
		
		fs.writeFileSync('./application.dat', _cryptor.decrypt(
			logInData.i2pkey_encoded
		), {
			encoding : "binary",
			flag     : "w+"
		});
		
		return "ok";
	}
}

if (!process.argv[2] && !process.argv[3]) {
	process.stdout.write('failed');
}
else {
	try {
		const database = require('./db-conn');
		const keyMd5 = crypt.md5(process.argv[2] + ":" + process.argv[3]);
		const cryptKey = new crypt.CryptKey(
			Buffer.from(keyMd5)
		);
		const cryptor = new crypt.AES(cryptKey);
		
		const logInData = database.get('users', new sql.Request([{
			login                : process.argv[2],
			password_key_encoded : cryptor.encrypt(Buffer.from(keyMd5))
		}]))[0];
		
		process.stdout.write(logInFunct(
			logInData,
			database,
			keyMd5,
			cryptor
		));
	}
	catch (e) {
		process.stdout.write(e.message);
		// process.stdout.write(e.stack);
	}
}