var http = require('http')
var url = require('url')

function start(route, handle) {
    function onRequest(request, response) {
        var pathname = url.parse(request.url).pathname
        console.log('received request for ' + pathname)

        var content = route(handle, pathname)
        response.writeHead(200, {'Content-Type': 'text/html'})
        response.write(content)
        response.end()
    }

    http.createServer(onRequest).listen(8888)
    console.log('listening ...')
}

exports.start = start

