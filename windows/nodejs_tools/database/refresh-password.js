const sql = require('sql-easy-lib');
const crypt = require('../cryptography/main-module');

function refreshPasswordFunct (database, oldCryptor, newCryptor) {
	// ... Здесь необходимо всё переподписать, обновить записи, защищённые старым паролем.
	process.stdout.write("ok");
}

try {
	const login = "";
	const oldPassword = "";
	const newPassword = "";
	
	const keyMd5Old = crypt.md5(login + ":" + oldPassword);
	const cryptKeyOld = new crypt.CryptKey(
		Buffer.from(keyMd5Old)
	);
	
	const keyMd5New = crypt.md5(login + ":" + newPassword);
	const cryptKeyNew = new crypt.CryptKey(
		Buffer.from(keyMd5New)
	);
	
	refreshPasswordFunct(
		require('./db-conn'),
		new crypt.AES(cryptKeyOld),
		new crypt.AES(cryptKeyNew)
	);
}
catch (e) {
	process.stdout.write(e.message);
}