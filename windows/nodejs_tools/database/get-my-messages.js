const sql = require('sql-easy-lib');
const database = require('../database/db-conn');
const crypt = require('../cryptography/main-module');
const fs = require('fs');

function getMyMessages () {
	// dialogId<:::>Логин пользователя>Входящее сообщение<:::><Исходящее сообщение<:::>...<!::>
	//                                                         Новый диалог (разделитель) --^ 
	const myselfId = database.get('envs', new sql.Request([{
		key : 'authedAccount'
	}]))[0].value;
	if (!myselfId) {
		return "not-authed";
	}
	const userKey = database.get('envs', new sql.Request([{
		key : 'activeKey'
	}]))[0].value;
	const userCryptor = new crypt.AES(
		new crypt.CryptKey(Buffer.from(userKey))
	);
	
	const messages = database.get('messages', new sql.Request([{
		fromId  : myselfId,
		ownerId : myselfId
	}, {
		toId    : myselfId,
		ownerId : myselfId
	}]));
	
	if (messages.length == 0) {
		return "null";
	}
	let myMessages = new Object();
	let messageString;
	let chatCryptor;
	let recipientObject;
	
	for (let message of messages) {
		chatCryptor = new crypt.AES(
			new crypt.CryptKey(
				userCryptor.decrypt(message.key, false)
			)
		);
		recipientObject = database.get('users', new sql.Request([{
			id : message.fromId
		}]))[0];
		// console.log(recipientObject);
		
		if (!myMessages[message.chatId]) {
			myMessages[message.chatId] = [ (message.fromId == myselfId ? "<" : `${recipientObject.login}>`) + chatCryptor.decrypt(message.message).toString().split("<:::>").join("?").split("<!::>").join("?") ];
		}
		else {
			myMessages[message.chatId].push((message.fromId == myselfId ? "<" : `${recipientObject.login}>`) + chatCryptor.decrypt(message.message).toString().split("<:::>").join("?").split("<!::>").join("?"));
		}
	}
	
	let output = new Array();
	for (let chatId in myMessages) {
		myMessages[chatId] = myMessages[chatId].join("<:::>");
		output.push(`${chatId}<:::>${myMessages[chatId]}`);
	}
	return output.join("<!::>")
}

try {
	process.stdout.write(getMyMessages());
}
catch (e) {
	process.stdout.write(e.message);
	// process.stdout.write("\n" + e.stack);
}