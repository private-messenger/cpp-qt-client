const request = require("request-promise");
const sql = require('sql-easy-lib');
const database = require('../database/db-conn');

async function main () {
	const toChat = process.argv[2];
	const message = process.argv.slice(3).join(' ');

	if (!toChat && !message) {
		process.stdout.write("Error: missed toChat, message");
	}
	else if (!toChat) {
		process.stdout.write("Error: missed toChat");
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
			i2pProxy.get({
				url : "http://localhost:49862/api/v1/messages.new",
				qs  : {
					to_chat : toChat,
					message : message
				},
				timeout : 25500
			});
			
			process.stdout.write("ok");
		}
		catch (err) {
			// console.log(err.name);
			// console.log(err);
			if (err.name == "StatusCodeError") {
				process.stdout.write(`Error: ${JSON.parse(err.response.body).error.code}`);
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