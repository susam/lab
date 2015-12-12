var http = require('http')
http.createServer(function (request, response) {
    console.log('received request')
    response.writeHead(200, {'Content-Type': 'text/plain'})
    response.write('hello world\n')
    response.end()
    console.log('sent response')
}).listen(8888)

console.log('listening ...')
