import time
import flask


app = flask.Flask(__name__)


@app.route('/')
def home():
    return """<!DOCTYPE html>
<html lang="en">
<head>
<title>Server Time (Ajax)</title>
<style>
body {background: beige; font-size: 2em; text-align: center}
button {font-size: 0.75em}
time {color: green}
</style>
</head>
<body>
<p>Server time: <time id="time">""" + formatted_time() + """</time></p>
<button id="button">Refresh via Ajax</button>
<script>
const button = document.getElementById('button')
const time = document.getElementById('time')
button.onclick = function () {
  const xhr = new XMLHttpRequest()
  xhr.open('GET', '/time')
  xhr.responseType = 'json'
  xhr.onload = function () {
    if (xhr.status === 200) {
      time.innerHTML = xhr.response.price
    } else {
      time.innerHTML = '[load error]'
    }
  }
  xhr.onerror = function () {
    time.innerHTML = '[xhr error]'
  }
  xhr.send()
}
</script>
</body>
</html>
"""


@app.route('/time')
def server_time():
    return flask.jsonify({'price': formatted_time()})


def formatted_time():
    return time.strftime('%H:%M:%S')


if __name__ == '__main__':
    from gevent.pywsgi import WSGIServer
    port = 8000
    server = WSGIServer(('', port), app)
    print('Starting server on port', port, '...')
    server.serve_forever()
