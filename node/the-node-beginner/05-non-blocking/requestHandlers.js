var child_process = require('child_process')

function start(response) {
    console.log('request handler start() was called')
    child_process.exec('sleep 5; echo start: hello, world',
                       function(error, stdout, stderr) {
        response.writeHead(200, {'Content-Type': 'text/plain'})
        response.write(stdout)
        response.end()
    })
}

function upload(response) {
    console.log('request handler upload() was called')
    response.writeHead(200, {'Content-Type': 'text/plain'})
    response.write('upload: hello, world\n')
    response.end()
}

exports.start = start
exports.upload = upload
