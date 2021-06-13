import json
import sys
import time
import flask

app = flask.Flask(__name__)


@app.route('/')
def home():
    return """<!DOCTYPE html>
<html lang="en">
<head>
<title>Server Time (Server Sent Event)</title>
<style>
body {background: beige; font-size: 2em; text-align: center}
button {font-size: 0.75em}
time {color: green}
</style>
</head>
<body>
<p>Server time: <time id="time">""" + formatted_time() + """</time></p>
<p id="refresh_interval" style="font-size:18px;"></p>
<script>
const time = document.getElementById('time')
const refresh_interval = document.getElementById('refresh_interval')
var eventSource = new EventSource('/time');
eventSource.onmessage = function (event) {
  jsonData = JSON.parse(event.data)
  time.innerHTML = jsonData.time
  refresh_interval.innerHTML = "(Refresh frequency "
                                 + jsonData.refresh_interval
                                 + "s)"
};
eventSource.onerror = function (event) {
  time.innerHTML = '[error]'
};
</script>
</body>
</html>
"""


@app.route('/time')
def stream():
    interval = int(sys.argv[1]) if len(sys.argv) > 1 else 1

    def event_stream():
        while True:
            time.sleep(interval)
            yield 'data: {}\n\n'.format(
                                    json.dumps({'time': formatted_time(),
                                                'refresh_interval': interval}))
    return flask.Response(event_stream(), mimetype='text/event-stream')


def formatted_time():
    return time.strftime('%H:%M:%S')


if __name__ == '__main__':
    from gevent.pywsgi import WSGIServer
    port = 8000
    server = WSGIServer(('', port), app)
    print('Starting server on port', port, '...')
    server.serve_forever()
