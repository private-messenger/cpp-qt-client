const sql = require('sql-easy-lib');
const fs = require('fs');
const crypt = require('../cryptography/main-module');
const { execSync } = require('child_process');

function getRandomArbitrary(min, max) {
    return Math.round(Math.random() * (max - min) + min);
}

function generateToken (length = 16) {
	let dict = "12334567890qwertyuiopasdfghjklzxcvbnm" + "qwertyuiopasdfghjklzxcvbnm".toUpperCase() + "-_=;$%!@";
	let generatedToken = "";
	for (let i=0; i < length; i++) {
		generatedToken += dict[getRandomArbitrary(0, dict.length - 1)];
	}
	return generatedToken;
}

function i2pKeyGen () {
	execSync('"i2p-tools/keygen" application.dat');
	return fs.readFileSync('./application.dat');
}

function finishRegister (i2pKey, id, activeKey) {
	//fs.writeFileSync('./application.dat', i2pKey);
	database.set('envs',
		new sql.Request([{
			key : 'authedAccount'
		}]),
		{
			value : id
		}
	);
	
	database.set('envs',
		new sql.Request([{
			key : 'activeKey'
		}]),
		{
			value : activeKey
		}
	);
}

if (!process.argv[2] && !process.argv[3]) {
	process.stdout.write("failed: no match required arguments: <login> <password>");
}
else {
	var database = require('./db-conn');
	
	try {
		const cryptKey = new crypt.CryptKey(
			Buffer.from(crypt.md5(process.argv[2] + ":" + process.argv[3]))
		);
		const rsaKey = crypt.generate();
		const aesCryptor = new crypt.AES(cryptKey);
		
		const id = generateToken(128);
		const i2pkey = i2pKeyGen();
		
		database.add('users', [{
			id                   : id,
			login                : process.argv[2],
			password_key_encoded : aesCryptor.encrypt(cryptKey.bytes),
			publickey            : rsaKey.public_key.bytes,
			privkey_encoded      : aesCryptor.encrypt(rsaKey.private_key.bytes),
			i2pkey_encoded       : aesCryptor.encrypt(i2pkey),
			storagekey_encoded   : aesCryptor.encrypt(cryptKey.bytes)  // (!) Написать нормальный ключ для хранилища в будущих апдейтах
		}]);
		
		finishRegister(i2pkey, id, cryptKey.bytes);
		
		process.stdout.write("ok");
	}
	catch (e) {
		process.stdout.write(e.message);
	}
}