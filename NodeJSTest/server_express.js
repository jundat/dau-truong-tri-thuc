

var express = require('express');
var app = express.createServer();
//app.use(express.logger());


app.post('/', function(req, res){
    res.send('Đấu trường tri thức');
});


app.post('/subject', function(req, res){
	var obj = {
		list:
		[
			{
				subjectId: 1,
				subjectName: "Khoa học tự nhiên"
			},
			{
				subjectId: 2,
				subjectName: "Lịch sử"
			},
			{
				subjectId: 3,
				subjectName: "Văn học"
			},
			{
				subjectId: 4,
				subjectName: "Nghệ thuật"
			},
			{
				subjectId: 5,
				subjectName: "Hiểu biết chung"
			}
		]
	};

    res.send(obj);
});


app.listen(8025, '127.0.0.1');
console.log('Express server started on port %s', 8025);


