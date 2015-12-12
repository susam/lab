function route(handle, pathname, request, response) {
    if (typeof handle[pathname] === 'function') {
        console.log('routing request for ' + pathname)
        handle[pathname](request, response)
    } else {
        console.log('no request handler for ' + pathname)
        response.writeHead(404, {'Content-Type': 'text/plain'})
        response.write('404 Not Found\n')
        response.end()
    }
}

exports.route = route
