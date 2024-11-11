function route(handle, pathname) {
    if (typeof handle[pathname] === 'function') {
        console.log('routing request for ' + pathname)
        return handle[pathname]()
    } else {
        console.log('no request handler for ' + pathname)
        return 'error: path does not exist\n'
    }
}

exports.route = route
