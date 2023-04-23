const njsbacker = require('njsbacker');
const methods   = require('./api');

class App extends njsbacker.Main {
	errorHadler (error) {
		console.log(error);
		return super.errorHadler(error);
	}
}

const app = new App();
const port = !process.argv[2] ? 49862 : +process.argv[2];  // Делается исключительно для тестирования, КРАЙНЕ НЕ СОВЕТУЮ менять порт при использовании программы
// const port = 49862;  // Делается исключительно для тестирования, КРАЙНЕ НЕ СОВЕТУЮ менять порт при использовании программы

for (let apiGroup in methods) {
	for (let method in methods[apiGroup]) {
		app.method(methods[apiGroup][method]);
	}
}

app.server('/api/v1').listen(port, async (err) => {
	if (err) { throw err; }
	else {
		console.log(`SERVER RUNNED AT ${port} PORT!`);
	}
});