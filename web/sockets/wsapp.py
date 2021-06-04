import json
import time
import flask
import flask_sockets


app = flask.Flask(__name__)
sockets = flask_sockets.Sockets(app)


@app.route('/')
def home():
    return """<!DOCTYPE html>
<html lang="en">
<head>
<title>Server Time (WebSocket)</title>
<style>
body {background: beige; font-size: 2em; text-align: center}
button {font-size: 0.75em}
time {color: green}
</style>
</head>
<body>
<p>Server time: <time id="time">""" + formatted_time() + """</time></p>
<button id="button">Refresh via WebSocket</button>
<script>
const button = document.getElementById('button')
const time = document.getElementById('time')
const ws = new WebSocket('ws://' + window.location.host + '/time')
button.onclick = function () {
  ws.send('get-time')
}
ws.onmessage = function (event) {
  time.innerHTML = JSON.parse(event.data).time
}
ws.onerror = function (event) {
  time.innerHTML = '[error]'
}
</script>
</body>
</html>
"""


@sockets.route('/time')
def server_time(ws):
    while not ws.closed:
        if ws.receive() == 'get-time':
            ws.send(json.dumps({'time': formatted_time()}))
        else:
            ws.send(json.dumps({'error': 'unknown command'}))


def formatted_time():
    return time.strftime('%H:%M:%S')


if __name__ == '__main__':
    import logging
    from gevent.pywsgi import WSGIServer
    from geventwebsocket.handler import WebSocketHandler
    logging.basicConfig(level=logging.INFO)
    port = 8000
    server = WSGIServer(('', port), app, handler_class=WebSocketHandler)
    print('Starting server on port', port, '...')
    server.serve_forever()
