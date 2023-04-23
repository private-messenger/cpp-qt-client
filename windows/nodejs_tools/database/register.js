const sql = require('sql-easy-lib');
const fs = require('fs');
const crypt = require('../cryptography/main-module');
const { execSync } = require('child_process');

function getRandomArbitrary(min, max) {
    return Math.round(Math.random() * (max - min) + min);
}

function generateToken (length = 16) {
	let dict = "12334567890qwertyuiopasdfghjklzxcvbnm" + "qwertyuiopasdfghjklzxcvbnm".toUpperCase();
	let generatedToken = "";
	for (let i=0; i < length; i++) {
		generatedToken += dict[getRandomArbitrary(0, dict.length - 1)];
	}
	return generatedToken;
}

function i2pKeyGen () {
	execSync('"i2p-tools/keygen" application.dat');
	return fs.readFileSync('./application.dat', {
		encoding: "binary"
	});
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

function getI2pPath () {
	let b32Key = execSync('"i2p-tools/keyinfo" application.dat').toString().split('\n').join('').split('\r').join('');
	return b32Key;
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
		
		if (process.argv[2].includes("<:::>") || (process.argv[2].includes("<!::>"))) {
			throw {
				message : 'Unsupported username'
			};
		}
		
		const id = generateToken(128);
		const i2pkey = i2pKeyGen();
		
		database.add('users', [{
			id                   : id,
			login                : process.argv[2],
			password_key_encoded : aesCryptor.encrypt(cryptKey.bytes),
			publickey            : rsaKey.public_key.bytes,
			privkey_encoded      : aesCryptor.encrypt(rsaKey.private_key.bytes),
			i2pkey_encoded       : aesCryptor.encrypt(i2pkey),
			'`b32-i2pAddress`'   : getI2pPath(),
			storagekey_encoded   : aesCryptor.encrypt(cryptKey.bytes),  // (!) Написать нормальный ключ для хранилища в будущих апдейтах
			updateTime           : Math.round(new Date().getTime() / 1000),
			isMyself             : 1
		}]);
		if (!database.get('users', new sql.Request([{ id }]), 'id')[0]) {
			throw {
				message : 'user will be not registered. SQLite3 error'
			};
		} 
		
		finishRegister(i2pkey, id, cryptKey.bytes);
		
		process.stdout.write("ok");
	}
	catch (e) {
		process.stdout.write(e.message);
	}
}