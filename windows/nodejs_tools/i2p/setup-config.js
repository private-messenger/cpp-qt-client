const sql = require('sql-easy-lib');
const database = require('../database/db-conn');
const fs = require('fs');
const path = require('path');

function setupConf () {
	const pathTunnels = database.get("envs", new sql.Request([{
		key : "i2pPathTunnels"
	}]), '`value`')[0].value;
	let config = fs.readFileSync(pathTunnels, {encoding:'utf8', flag:'r'});
	let configValid = `[HTTP-SPIK]
type   = http
host   = 127.0.0.1
port   = 49862
inport = 80
keys   = application.dat
gzip   = false`;
	if (!config.includes(configValid)) {
		if (config[0] != "\n") config = "\n" + config;
		config = configValid + "\n" + config;
		fs.writeFileSync(pathTunnels, config);
	}
	return "ok";
}

try {
	process.stdout.write(setupConf());
}
catch (e) {
	process.stdout.write(e.message);
	// process.stdout.write("\n" + e.stack);
}