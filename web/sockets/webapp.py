import time
import flask


app = flask.Flask(__name__)


@app.route('/')
def home():
    return """<!DOCTYPE html>
<html lang="en">
<head>
<title>Server Time</title>
<style>
body {background: beige; font-size: 2em; text-align: center}
button {font-size: 0.75em}
time {color: green}
</style>
</head>
<body>
<p>Server time: <time>""" + formatted_time() + """</time></p>
<button id="button">Refresh page</button>
<script>
const button = document.getElementById('button')
button.onclick = function () {
  window.location.reload()
}
</script>
</body>
</html>
"""


def formatted_time():
    return time.strftime('%H:%M:%S')


if __name__ == '__main__':
    from gevent.pywsgi import WSGIServer
    port = 8000
    server = WSGIServer(('', port), app)
    print('Starting server on port', port, '...')
    server.serve_forever()
