const sql = require('sql-easy-lib');
//const fs = require('fs');
const database = require('./db-conn');
const crypt = require('../cryptography/main-module');

function getKeys () {
	/*
	Синтаксис ключа: Имя ключа<:::>тип шифрования<:::>Код типа (0 - симметричный; 1 - асимметричный, публичный; 2 - асимметричный, приватный)<:::>кодировка<:::>Сам ключ<!::>
	                                                                                                                                                                      ^-- Разделитель ключей
	*/
	// Проверим авторизацию
	let myselfId = database.get('envs', new sql.Request([{
		key : 'authedAccount'
	}]))[0].value;
	if (!myselfId) {
		return "not-authed";
	}
	
	let keyList = new Array();
	// Ключи от аккаунтов тоже считаются!
	let keyUsed = database.get('envs', new sql.Request([{
		key : 'activeKey'
	}]))[0].value;
	
	let userKeys = database.get("users", new sql.Request([{
		id : myselfId
	}]), 'login, publickey, privkey_encoded, i2pkey_encoded, storagekey_encoded')[0];
	
	const cryptKey = new crypt.CryptKey(
		Buffer.from(keyUsed)
	);
	const aesCryptor = new crypt.AES(cryptKey);
	
	keyList.push({
		name   : "Public Key",
		type   : "RSA",
		ktpe   : "1",
		key    : userKeys.publickey.toString(),
		coding : "utf8"
	});
	keyList.push({
		name   : "Private Key",
		type   : "RSA",
		ktpe   : "2",
		key    : aesCryptor.decrypt(userKeys.privkey_encoded).toString(),
		coding : "utf8"
	});
	keyList.push({
		name   : "Personal Account Key",
		type   : "AES",
		ktpe   : "0",
		key    : keyUsed,
		coding : "utf8"
	});
	keyList.push({
		name   : "I2p Key",
		type   : "Diffie–Hellman key exchange (i2p)",
		ktpe   : "0",
		key    : Buffer.from(aesCryptor.decrypt(userKeys.i2pkey_encoded)).toString('base64'),
		coding : "base64"
	});
	let keyPull = new Array ();
	let keys = database.get('messages', new sql.Request([{
		ownerId : myselfId,
	}]), 'key, chatId').map(i => ({key : i.key, description : `Key of chat id: ${i.chatId}`})).filter(i => {
		let result = true;
		if (keyPull.indexOf(i.key.toString('base64')) != -1) {
			result = false;
		}
		else keyPull.push(i.key.toString('base64'));
		return result;
	});
	
	/*let rsaCryptor = new crypt.Crypt({
		private_key : new crypt.CryptKey(Buffer.from(aesCryptor.decrypt(userKeys.privkey_encoded))),
		public_key  : new crypt.CryptKey(Buffer.from(userKeys.publickey))
	});*/
	for (let myKey of keys) {
		keyList.push({
			name   : myKey.description,
			type   : "AES",
			ktpe   : "0",
			key    : aesCryptor.decrypt(myKey.key, false).toString('base64'),
			coding : "base64"
		});
	}
	
	// Собираем ключи в единую строку
	return keyList.map(i => `${i.name}<:::>${i.type}<:::>${i.ktpe}<:::>${i.coding}<:::>${i.key}`).join('<!::>');
}

try {
	process.stdout.write(getKeys());
}
catch (e) {
	process.stdout.write(e.message);
}