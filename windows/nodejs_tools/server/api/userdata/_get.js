const njsbacker = require('njsbacker');
const sql = require('sql-easy-lib');
const connectDb = () => require('../../../database/db-conn');

class Get extends njsbacker.Method {
	execute (params, session, groups) {
		let database = connectDb();
		let toggleId = database.get('envs', new sql.Request([{
			key : 'authedAccount'
		}]))[0].value;
		if (!toggleId) {
			throw new njsbacker.ApiError('USER_NOT_LOGGED_IN', null);
			return;
		}
		return database.get('users', new sql.Request([{
			id : toggleId
		}]), 'id, login, publickey, updateTime').map(i => {
			i.publickey = i.publickey.toString();
			return i;
		})[0];
	}
}

module.exports = new Get('userdata.get', '/userdata.get', {
	_ : {
		required : false,
		type : njsbacker.types.string,
		conversion : false,
		allow_methods : ['get']
	}
});