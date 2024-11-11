var http = require('http')
var url = require('url')

function start(route, handle) {
    function onRequest(request, response) {
        var pathname = url.parse(request.url).pathname
        console.log('received request for ' + pathname)

        var data = ''
        request.addListener('data', function(chunk) {
            console.log('received data chunk "' + chunk + '"')
            data += chunk
        })

        request.addListener('end', function(chunk) {
            console.log('reached end of data')
            route(handle, pathname, response, data)
        })
    }

    http.createServer(onRequest).listen(8888)
    console.log('listening ...')
}

exports.start = start
