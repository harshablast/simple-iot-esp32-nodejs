const express = require('express');
const app = express();
const port = process.env.PORT || 3000;

var bodyParser = require('body-parser');

var led_state = 0;
var sensor_value;

app.use(bodyParser.json());

app.get('/', (req, res) => {

	res.sendFile(__dirname + '/index.html');

});

app.get('/ledstate', (req, res) => {

	res.setHeader('Content-Type', 'text/plain');
	res.status(200);
	res.send(led_state.toString());

});

app.post('/sensordata', (req, res) => {

	sensor_value = parseInt(req.body.sensor_value);
	
	res.status(200);
	res.send("Sensor data sent successfully");

});

app.post('/updateled', (req, res) => {

	console.log(req.body);

	led_state = parseInt(req.body.led_state);
	
	res.status(200);
	res.send("LED State send successfully");

});

app.listen(port, () => console.log("Server listening"));