function sleep(ms) {
    var startTime = new Date().getTime()
    while (new Date().getTime() - startTime < ms)
        ;
}

function start() {
    console.log('request handler start() was called')
    sleep(5000)
    return 'start: hello, world\n'
}

function upload() {
    console.log('request handler upload() was called')
    return 'upload: hello, world\n'
}

exports.start = start
exports.upload = upload
