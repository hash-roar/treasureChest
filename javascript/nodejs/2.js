let http = require('http');

let server = http.createServer();

server.on("request",function(request,response){
	console.log("client:-->"+request.url);
	response.write("hello");
	response.end();
})
server.listen(8880);
