const request = require("request-promise");
const sql = require('sql-easy-lib');
const database = require('../database/db-conn');

async function main () {
	const toId = process.argv[2];
	const message = process.argv.slice(3).join(' ');

	if (!toId && !message) {
		process.stdout.write("Error: missed toId, message");
	}
	else if (!toId) {
		process.stdout.write("Error: missed toId");
	}
	else if (!message) {
		process.stdout.write("Error: missed message");
	}
	else {
		const i2pPort  = database.get("envs", new sql.Request([{
			key : "i2pPortHttp"
		}]))[0].value;
		// const i2pProxy = request.defaults({ proxy : `http://127.0.0.1:${i2pPort}` });
		const i2pProxy = request;
		try {
			const response = await i2pProxy.get({
				url : "http://localhost:49862/api/v1/messages.startDialog",
				qs  : {
					to_id   : toId,
					message : message
				},
				timeout : 20000
			});
			// console.log(response);
			// const result = JSON.parse(response);
			
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