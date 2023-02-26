const crypt = require('./main-module');
//console.log(process.argv);
if (!process.argv[2] && !process.argv.slice(3).join(' ')) {
	process.stdout.write('');
}
else {
	encryptionData = Buffer.from(process.argv.slice(3).join(' '));
	key = new crypt.CryptKey(Buffer.from(process.argv[2]));
	if ([16, 32, 64, 128, 256].indexOf(key.bytes.length) == -1) {
		process.stdout.write('');
	}
	else {
		aesEncryptor = new crypt.AES(key);
		process.stdout.write(aesEncryptor.encrypt(encryptionData).toString());
	}
}