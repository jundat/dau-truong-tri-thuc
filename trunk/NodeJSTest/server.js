

var express = require('express');
var app = express.createServer();
app.use(express.logger());


app.post('/', function(req, res){
    res.send('Đấu trường tri thức');
});

app.post('/score', function(req, res){	
	console.log(req.param("data"));
    res.send(req.param("data"));
});

app.get('/score', function(req, res){	
	console.log(req.param("data"));
    res.send(req.param("data"));
});

app.listen(8025, '127.0.0.1');
console.log('Express server started on port %s', 8025);


