var socket = io.connect(location.origin);

socket.on('newdata', function(data) {
	for(var i in data) {
		document.querySelector('#'+i+' .value').textContent = data[i];
	}
});

document.querySelector('#gimmethedata').addEventListener('click', function() {
	socket.emit('gimmethedata');
});