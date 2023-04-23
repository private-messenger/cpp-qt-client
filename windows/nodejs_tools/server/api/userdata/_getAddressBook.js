const njsbacker = require('njsbacker');
const sql = require('sql-easy-lib');
const connectDb = () => require('../../../database/db-conn');

class GetAddressBook extends njsbacker.Method {
	execute (params, session, groups) {
		let database = connectDb();
		let users = database.get('users', new sql.Request([{ isMyself : 1 }]), 'id, login, publickey, updateTime, `b32-i2pAddress`').map(i => {
			i.publickey = i.publickey.toString();
			return i;
		});
		let count = users.length;
		let limit = parseInt(database.get('envs', new sql.Request([{
			key : "maxAddressBook"
		}]))[0].value);
		return { count, limit, users };
	}
}

module.exports = new GetAddressBook('userdata.getAddressBook', '/userdata.getAddressBook', {
	_ : {
		required : false,
		type : njsbacker.types.string,
		conversion : false,
		allow_methods : ['get']
	}
});