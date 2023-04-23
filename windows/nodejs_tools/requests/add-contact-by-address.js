const request = require("request-promise");
const sql = require('sql-easy-lib');
const database = require('../database/db-conn');

async function main () {
	const address = process.argv[2];

	if (!address) {
		process.stdout.write("Error: missed address");
	}
	else {
		const myselfId = database.get('envs', new sql.Request([{
			key : 'authedAccount'
		}]))[0].value;
		if (!myselfId) {
			return "not-authed";
		}
		
		const i2pPort  = database.get("envs", new sql.Request([{
			key : "i2pPortHttp"
		}]))[0].value;
		const i2pProxy = request.defaults({ proxy : `http://127.0.0.1:${i2pPort}` });
		// const i2pProxy = request;
		try {
			const response = await i2pProxy.get({
				url : `http://${address}/api/v1/userdata.get`,
				qs  : {},
				timeout : 10000
			});
			// console.log(response);
			const result = JSON.parse(response).result;
			try {
				
				database.add('users', [{
					id                   : result.id,
					login                : result.login,
					password_key_encoded : null,
					publickey            : result.publickey,
					privkey_encoded      : null,
					i2pkey_encoded       : null,
					'`b32-i2pAddress`'   : address,
					storagekey_encoded   : null,
					isMyself             : 0,
					updateTime           : result.updateTime,
					storagedAccount      : 1
				}]);
			}
			catch (e) {
				console.log(e.stack);
			}
			
			try {
				database.add('`contact-book`', [{
					row       : database.getIndex('`contact-book`', 'row'),
					ownerId   : myselfId,
					contactId : result.id
				}]);
			}
			catch (e) {
				console.log(e.stack);
			}
			
			process.stdout.write("ok");
		}
		catch (err) {
			// console.log(err.name);
			// console.log(err);
			if (err.name == "StatusCodeError") {
				let errorStatus = `Status code is ${err.statusCode}`;
				try {
					errorStatus = JSON.parse(err.response.body).error.code
				}
				catch (_e) {}
				process.stdout.write(`Error: ${errorStatus}`);
			}
			else if (err.name == "RequestError") {
				process.stdout.write(`Error: Response time out`);
			}
			else {
				process.stdout.write("Error: " + err.message);
			}
		}
	}
}

main();