const sql = require('sql-easy-lib');

/*
Порядок следования:
<maxAddressBook>
<maxPeronalAddress>
*/

function setGeneralSettingsFunct (database, settings) {
	if (settings.maxAddressBook) {
		database.set('envs', new sql.Request([{
			key   : 'maxAddressBook'
		}]), {
			value : settings.maxAddressBook
		});
	}
	
	if (settings.maxPeronalAddress) {
		database.set('envs', new sql.Request([{
			key   : 'maxPeronalAddress'
		}]), {
			value : settings.maxPeronalAddress
		});
	}
	
	process.stdout.write("ok");
}