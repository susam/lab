var server = require('./server')
var router = require('./router')
var requestHandlers = require('./requestHandlers')

var handle = {
    '/': requestHandlers.start,
    '/start': requestHandlers.start,
    '/upload': requestHandlers.upload
}

server.start(router.route, handle)

// The request handler, requestHandlers.start, is blocking. To test
// this, run the following two curl commands one after another while
// ensuring that the second command is run while the first command is
// still running.
//
//   curl -v http://localhost:8888/
//   curl -v http://localhost:8888/upload
//
// The first command would take 5 seconds to return a response. During
// this time, when the second command runs it is blocked until the first
// command returns a response. This happens because
// requestHandlers.start blocks itself for 5 seconds.
