var querystring = require('querystring')
var fs = require('fs')
var formidable = require('formidable')

function start(request, response) {
    console.log('request handler start() was called')
    var body = '<!DOCTYPE html>' +
               '<html><head><title>Start</title>' +
               '<meta charset="UTF-8">' +
               '</head><body>' +
               '<form action="/upload"" enctype="multipart/form-data"' +
               'method="post">' +
               'Text: <input name="text"><br>' +
               '<input type="file" name="upload"><br>' +
               '<input type="submit" value="Upload">' +
               '</form>' +
               '</body></html>\n'
    response.writeHead(200, {'Content-Type': 'text/html'})
    response.write(body)
    response.end()
}

function upload(request, response) {
    console.log('request handler upload() was called')

    var form = new formidable.IncomingForm()
    form.parse(request, function (error, fields, files) {
        console.log('parsed fields:', fields)
        console.log('parsed files:', files)

        // It is necessary to set enctype="multipart/form-data" in the
        // form, otherwise only text=foo&upload=s.png would be sent as
        // POST data. The content of s.png would not be sent. As a
        // result, the following error would occur:
        //
        // TypeError: Cannot read property 'path' of undefined

        fs.unlink('/tmp/s.png', function(error) {
            if (error) {
                console.log('cannot remove image file:', error.message)
            }
            fs.rename(files.upload.path, '/tmp/s.png', function (error) {
                console.log('sending response ...')
                response.writeHead(200, {'Content-Type': 'text/html'})
                response.write('<p>post text: ' + fields.text + '</p>')
                response.write('<br>')
                if (error) {
                    console.log('cannot rename upload file:', error.message)
                    response.write('<p>error while uploading file</p>')
                    response.end()
                } else {
                    console.log('renamed upload file')
                    response.write('<img src="/show">')
                    response.end()
                }
            })
        })
    })

    console.log('writing head ...')
}

function show(request, response) {
    console.log('request handler show() was called')
    response.writeHead(200, {'Content-Type': 'image/png'})
    fs.createReadStream('/tmp/s.png').pipe(response)
}

exports.start = start
exports.upload = upload
exports.show = show
