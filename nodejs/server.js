var SerialPort = require('serialport').SerialPort;
var serialPort = require("serialport");
var fs = require('fs');
var express = require('express');
var app = express();

var express = require('express');
var http = require('http');
var path = require('path');

var app = express();

// all environments
app.set('port', process.env.PORT || 3000);
app.use(express.favicon());
app.use(express.static(path.join(__dirname, 'public')));

// development only
if ('development' == app.get('env')) {
	app.use(express.errorHandler());
}

var server = http.createServer(app);

server.listen(app.get('port'), function() {
	console.log('Express server listening on port ' + app.get('port'));
});

var io = require('socket.io').listen(server);

var portName = '/dev/tty.usbmodem1411';
var sp = new SerialPort(portName, {
	baudRate: 9600,
	dataBits: 8,
	parity: 'none',
	stopBits: 1,
	flowControl: false
});


var receivedData = '';
sp.on('open', function() {
	console.log('serial communication opened');
	// Listens to incoming data
	var dane = '';
	sp.on('data', function(data) {

		receivedData += data.toString();

		if (receivedData.indexOf('^') >= 0 && receivedData.indexOf('#') >= 0) {
			sendData = receivedData.substring(receivedData.indexOf('^') + 1, receivedData.indexOf('#'));
			receivedData = '';

			pushToClients(sendData);
		}
	});

	// serialPort.list -> callback
	// https://www.npmjs.org/package/serialport -> poszukaj sobie serialPort.list

});
setInterval(function() {
	sp.write('$2;0\n');
}, 10000);
io.sockets.on('connection', function(socket) {
	socket.on('gimmethedata', function() {
		sp.write('$2;0\n');
	});
});

function pushToClients(data) {
	data = data.split(';');
	if (data.length === 5) {
		var sendData = {
			deviceNumber: data[0],
			temperature: data[1],
			humidity: data[2],
			p1: data[3],
			p2: data[4]
		};
		io.sockets.emit('newdata', sendData);
	} else {
		console.info('not expected data: %s', data);
	}

	
}