const njsbacker = require('njsbacker');
const connectDb = () => require('../../database/db-conn');

const int16bit = {
	long_name   : 'int16bit',
	short_name  : 'int16',
	checkSchema : (value, schema) => njsbacker.types.integer.checkSchema(value, schema),
	syntax : (value, needs_convert = false) => {
		let [success, val] = njsbacker.types.integer.syntax(value, needs_convert = false);
		if (!success) {
			return [false, undefined];
		}
		if (parseInt(val) > 255 || parseInt(val) < 0) {
			return [false, undefined];
		}
		else {
			return [true, val];
		}
	}
};

const usertype = njsbacker.types.string;

module.exports = { int16bit, usertype };