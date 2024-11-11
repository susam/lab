var http = require('http')
var url = require('url')

function start() {
    function onRequest(request, response) {
        var pathname = url.parse(request.url).pathname
        console.log('received request for ' + pathname)
        response.writeHead(200, {'Content-Type': 'text/html'})
        response.write('hello, world\n')
        response.end()
    }

    http.createServer(onRequest).listen(8888)
    console.log('listening ...')
}

// The name of the exports property be different from the name of the
// function assigned to it.
exports.run = start
