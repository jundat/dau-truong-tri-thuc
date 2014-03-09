// var http = require('http');

// http.createServer(function (req, res) {
//   	res.writeHead(200, {'Content-Type': 'text/plain'});
//   	res.end('Hello World');
// }).listen(1337, '127.0.0.1');

// console.log('Server running at http://127.0.0.1:1337/');


var http = require("http");
var url = require("url");
 
http.createServer(function (req, res) {
    var POST = url.parse(req.url, true).query; 
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end(POST['data']);
}).listen(8025, '127.0.0.1');

console.log('Server running at http://127.0.0.1:8025');

//