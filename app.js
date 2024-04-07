const express = require('express');
const app = express();
const http = require('http').createServer(app);
const io = require('socket.io')(http);
const fs = require('fs');
const SerialPort = require('serialport');
const parsers = SerialPort.parsers;
const parser = new parsers.Readline({ delimiter: '\r\n' });

const port = new SerialPort('COM5', {
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false
});

const index = fs.readFileSync('index.html');

let temperature = 0;
let tds = 0;
let pH = 0;

app.get('/', function(req, res) {
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.end(index);
});

app.get('/naman', function(req, res) {
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.end(JSON.stringify({ temperature: temperature, tds: tds, pH: pH }));
});

port.pipe(parser);

io.on('connection', function(socket) {
    console.log('Node is listening to port');
    socket.on('data', function(data) {
        const dataArray = data.split(',');
        temperature = parseFloat(dataArray[0]);
        tds = parseFloat(dataArray[1]);
        pH = parseFloat(dataArray[2]);
        // Emit the updated data to all connected clients
        io.emit('data', { temperature, tds, pH });
    });
});

parser.on('data', function(data) {
    console.log('Received data from port: ' + data);
    // Update the /naman endpoint with the latest data
    const dataArray = data.split(',');
    temperature = parseFloat(dataArray[0]);
    tds = parseFloat(dataArray[1]);
    pH = parseFloat(dataArray[2]);
    io.emit('updateData', { temperature, tds, pH });
});

http.listen(3000, function() {
    console.log('Server is listening on port 3000');
});
