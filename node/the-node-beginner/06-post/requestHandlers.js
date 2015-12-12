var querystring = require('querystring')

function start(response, data) {
    console.log('request handler start() was called')
    var body = '<!DOCTYPE html>' +
               '<html><head><title>Start</title>' +
               '<meta charset="UTF-8">' +
               '</head><body>' +
               '<form action="/upload" method="post">' +
               '<textarea name="text" rows="20" cols="60"></textarea>' +
               '<br>' +
               '<input type="submit" value="Submit">' +
               '</form>' +
               '</body></html>\n'
    response.writeHead(200, {'Content-Type': 'text/html'})
    response.write(body)
    response.end()
}

function upload(response, data) {
    console.log('request handler upload() was called')
    response.writeHead(200, {'Content-Type': 'text/plain'})
    response.write('post data: ' + querystring.parse(data).text)
    response.end()
}

exports.start = start
exports.upload = upload
