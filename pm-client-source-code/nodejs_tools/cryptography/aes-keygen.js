const generateAES = require('./main-module').generateAES;

process.stdout.write(generateAES().key.bytes.toString());