From Sockets to WebSockets
==========================

This directory contains some experimental code that allows us to see
plain TCP socket-based application, a simple HTTP web application, an
AJAX-based application, SSE-based application, and a WebSocket-based
application in action and study the underlying application layer
payloads that are exchanged between the client and the server while
each application is running. All code here is minimal in nature. No
encryption is used. There is very little error handling. The objective
here is limited to comparing only the application layer payloads
resulting from the various programs.

To see only what the payloads look like for each example application,
go to section [Payloads](#payloads). To run the example programs on
your system, continue reading with the next section.


Contents
--------

* [Background](#background)
* [Setup](#setup)
* [Run Example Apps](#run-example-apps)
  * [TCP Socket App](#tcp-socket-app)
  * [Web App](#web-app)
  * [Ajax App](#ajax-app)
  * [SSE App](#sse-app)
  * [Websocket App](#websocket-app)
* [Packet Captures](#packet-captures)
  * [Overall Statistics](#overall-statistics)
  * [Per Update Statistics](#per-update-statistics)
  * [Legend](#legend)
* [Payloads](#payloads)
  * [TCP Socket App Payloads](#tcp-socket-app-payloads)
  * [Web App Payloads](#web-app-payloads)
  * [Ajax App Payloads](#ajax-app-payloads)
  * [SSE App Payloads](#sse-app-payloads)
  * [WebSocket App Payloads](#websocket-app-payloads)
* [Thanks](#thanks)


Background
----------

The programs in this directory implement very simple and minimal
server programs that send the server's current time to the client. The
same functionality is implemented in five different ways: TCP socket
program, plain web application, Ajax-based web application, SSE-based
web application, and Websocket-based web application. The list below
talks about these different approaches in a general manner.

  - TCP sockets: A server program listens on a TCP port. A client
    program connects to it. Once the connection has been established
    either party can send messages to each other. The usage of TCP
    sockets to develop network applications became popular in the
    1980s. TCP offers a full-duplex, connection-oriented channel for
    exchanging data stream between the server and client. In 1983, the
    Berkeley socket API was created 4.2BSD Unix to create and work
    with sockets. It soon became a de facto standard for working with
    sockets. The POSIX as well as Windows socket APIs are based on it.

  - Dynamic web application: A server application is served via a web
    server. The server application serves a dynamically generated web
    page that can be viewed using a web browser. This approach became
    popular in the early 1990s as the world wide web rose in
    popularity. Technologies like PHP, CGI, ASP, etc. were used to
    serve dynamic web pages in the early days. Now there are many
    frameworks available for almost every major programming language
    to create and serve dynamic web pages. If any component in the
    page needs to be updated, the whole page has to be refreshed.
    Often the dynamic content is separated out into a tiny page that
    is loaded in an `<iframe>` element within a larger web page, so
    that updating the dynamic content involves reloading only the tiny
    page within the `<iframe>` element, not the entire larger page.
    Such dynamic pages within a `<iframe>` element may be designed to
    reload automatically every few seconds or minutes. The `<iframe>`
    element was first introduced in Internet Explorer by Microsoft in
    1996.

  - Ajax-based web application: The server serves a web page with
    JavaScript code embedded in it to the client. When some dynamic
    content in the page needs to be updated, the JavaScript code runs
    on the web browser and sends a so-called Asynchronous JavaScript
    and XML (AJAX, also written as Ajax) request to the server. An
    Ajax request is in fact an HTTP request but it is called so due to
    the fact that it can be invoked asynchronously after a page has
    been loaded without having to reload the entire web page. After
    the server responds with the requested data, the JavaScript code
    updates the web page's Document Object Model (DOM) to display the
    updated data on the web browser. This approach avoids reloading
    the entire web page to display updated dynamic data. This approach
    became popular in the early 2000s when Microsoft used it to
    implement dynamic updates in Outlook Web Access. XML was a popular
    data interchange format in the early days but now JSON has
    overtaken it in popularity.

  - SSE-based web application: SSE stands for server-sent events. The
    server pushes continuous updates in form of events to the client
    after the initial connnection is established. SSE is
    unidirectional where events are sent only from server to the
    clients. The server sends the events using MIME type
    `text/event-stream`. Each event sent by the server is in the form
    of a text block terminated by a pair of newlines. SSE has a
    limitation of maximum number of open connections. This limit is 6
    and is per domain + browser. It means that one can open only 6 SSE
    connections across all of the browser tabs to a domain. Opera was
    the first browser to support SSE in 2006. Since, then all major
    browsers except Internet Explorer have supported SSE.

  - WebSocket-based web application: The server serves a web page with
    JavaScript code embedded in it to the client. The JavaScript code
    executes on the web browser and makes an HTTP request to the
    server. The request contains HTTP headers (`Connection: Upgrade`,
    `Upgrade: websocket`, etc.) to request the web server to upgrade
    the communication protocol to WebSocket. The WebSocket protocol is
    a bidirectional, stateful protocol that is designed to work over
    HTTP. After the web server agrees to upgrade the protocol to
    WebSocket, either the server or the client can send messages to
    each other via the WebSocket without having to create new
    full-blown HTTP requests. This approach became popular in the
    2010s, especially, to implement chat applications and other
    applications that require frequent updates. This avoids the need
    for the client to poll the server periodically as is common in the
    Ajax approach. In December 2009, Google Chrome 4 was the first
    browser to ship full support for WebSockets. Now it is available
    as a standard feature in most major browsers.

Note that this document does not concern itself with Socket.IO at all.
Socket.IO is a JavaScript library that enables real-time,
bidirectional, event-based communication between web clients and
server. Socket.IO uses WebSocket internally but it also supports
falling back to HTTP long-polling (a popular approach for Ajax-based
applications) if support for WebSocket is not found in the web client.
This document concerns itself with WebSocket only, not Socket.IO.


Setup
-----

This section and the next one describes how to set up a virtual Python
environment and run the example programs available in this directory.
To skip running the programs and instead read about the packet
captures and the application layer payloads, go directly to section
[Packet Captures](#packet-captures) or section [Payloads](#payloads).

Perform the following steps to set up a virtual Python environment to
run the example programs:

 1. The environment for experimentation depends on these tools: Git,
    Python 3, Netcat, a modern web browser. On a recent version of
    macOS (e.g., macOS Catalina 10.15), these tools are available by
    default. In case these tools are missing on your system or if you
    want recent versions of these tools, on macOS you may install them
    using [Homebrew](https://brew.sh/) with this command:

    ```sh
    brew install git netcat python
    ```

    On Debian, Ubuntu, or a similar system, enter the following
    command:

    ```sh
    apt-get update
    apt-get install git netcat python3 python3-venv python3-dev gcc make
    ```

    Note that `python3-dev`, `gcc`, and `make` are required on Debian
    to build `gevent`, a required dependency to be able to run most of
    the example programs in this directory.

 2. Clone this repository and make this directory the current
    directory:

    ```sh
    git clone https://github.com/susam/lab.git
    cd lab/web/sockets
    ```

 3. Set up a virtual Python environment to run the code examples in:

    ```sh
    python3 -m venv ~/.venv/websockets
    . ~/.venv/websockets/bin/activate
    pip3 install -r requirements.txt
    ```

 4. Perform a sanity check to ensure your virtual Python environment
    is set up. First run the program that runs a simple
    websocket-based time service:

    ```sh
    python3 wsapp.py
    ```

    Then visit http://localhost:8000/ with a web browser. A web page
    with the current time should appear. Then click on the "Refresh
    via WebSocket" button after a few seconds. An updated time should
    appear.

From here on, anytime you want to run an example program available in
this directory, you must run it the virtual Python environment set up
just now. The string `(websockets)` at the beginning of the shell
prompt shows that you are in the virtual Python environment. In case
you lose the virtual Python environment for any reason, run
`. ~/.venv/websockets/bin/activate` to activate it again.

The remaning sections explain how to run and use each example program.


Run Example Apps
----------------

### TCP Socket App

Perform the following steps to run the simple TCP socket app
[tcpapp.py] and interact with it:


 1. Enter the following command to run the TCP server program:

    ```sh
    python3 tcpapp.py
    ```

 2. Then run Netcat to connect to the application and fetch the
    current time on the server:

    ```sh
    nc localhost 8000
    ```

 3. Type `time` into Netcat and press <kbd>Enter</kbd> to get the
    current time. Here is an example Netcat session with the server
    program:

    ```
    $ nc localhost 8000
    Hello!
    Server time: 16:11:05

    time
    16:11:07

    time
    16:11:09

    time
    16:11:09

    bye
    Good bye!
    ```

Note that if multiple clients connect to the TCP server program
simultaneously, the server accepts and handles the connections
sequentially. This has been done so to keep the program extremely
simple since the focus here is on inspecting the packet data, not
developing a robust server program.


### Web App

Perform the following steps to run the simple web app [webapp.py] and
interact with it:

  1. Enter the following command to run the simple web app server
     program:

     ```sh
     python3 webapp.py
     ```

  2. Visit http://localhost:8000/ with a web browser. A web page with
     the current time should appear.

  3. Click the "Refresh page" button. Updated time should appear.

Note that a typical web application like this may automatically
refresh the web page automatically every few seconds or minutes so
that the updated data appears automatically on the web browser without
requiring manual action from the user. In the example program provided
here, the user needs to manually click on a button to reload the page.
None of the examples provided here update the dynamic content
automatically, so that we can manually refresh the content when we
need. This allows us to control the generation of payloads manually so
that we can observe them conveniently using a packet capture tool.


### Ajax App

Perform the following steps to run the Ajax-based app [ajaxapp.py] and
interact with it:

  1. Enter the following command to run the simple web app server
     program:

     ```sh
     python3 ajaxapp.py
     ```

  2. Visit http://localhost:8000/ with a web browser. A web page with
     the current time should appear.

  3. Click the "Refresh with Ajax" button. Updated time should appear.


### SSE App

Perform the following steps to run the SSE-based app [sseapp.py] and
interact with it:

 1. Enter the following command:

    ```sh
    python3 sseapp.py
    ```

 2. Visit http://localhost:8000/ with a web browser. A web page with
    the current time should appear. The time will update every one
    second (default behaviour).

This program also supports custom refresh interval for the time. For
example, to increase the refresh interval to, say, 10 seconds run
`python3 sseapp.py 10`. The additional command line argument specifies
the time refresh interval in number of seconds. When this additional
argument is missing, the time refresh interval defaults to 1 second.


### WebSocket App

Perform the following steps to run the WebSocket-based app [wsapp.py]
and interact with it:

 1. Enter the following command:

    ```sh
    python3 wsapp.py
    ```

 2. Visit http://localhost:8000/ with a web browser. A web page with
    the current time should appear.

 3. Click the "Refresh via WebSocket" button. Updated time should
    appear.


Packet Captures
---------------

Packet captures for each example program is available in the [pcap]
directory. The timeline for each packet capture (PCAP) roughly looks
like this:

| Time          | Description                                        |
| ------------- | -------------------------------------------------- |
| 00:00:00      | Client connects to server and obtains current time |
| 00:00:10      | Client sends a request to obtain current time      |
| 00:00:20      | Client sends a request to obtain current time      |
| 00:00:30      | Client sends a request to obtain current time      |
| 00:00:40      | Client is closed                                   |

The only exception to the above timeline is the server-sent
event-based program in [sseapp.py]. Since SSE establishes a
unidirectional stream of events, there is no request going from
client to server to obtain current time. The timeline for the PCAP of
SSE example looks like this:

| Time          | Description                                        |
| ------------- | -------------------------------------------------- |
| 00:00:00      | Client connects to server and obtains current time |
| 00:00:10      | Server sends current time to client                |
| 00:00:20      | Server sends current time to client                |
| 00:00:30      | Server sends current time to client                |
| 00:00:35      | Client is closed                                   |

Each example program was run on a Linode virtual machine running
Debian GNU/Linux 10.9 (buster). The PCAPs were obtained by running the
following command on the Debian system:

```sh
tcpdump -i eth0 -w filename.pcap port 8000
```

For the TCP socket app, Netcat 46.40.1 was used to connect to it from
a macOS Catalina 10.15.7. For the other web apps, Firefox 89.0 was
used to connect to them from the same macOS system.

These PCAPs can be read using software tools that understand the PCAP
format. Some popular tools for reading PCAPs are Wireshark, Tshark,
Tcpdump, etc. The TXT files in the [pcap] directory contain
human-readable packet data automatically parsed out from the PCAP
files.


### Overall Statistics

Here is an overall summary of some packet details found in the packet
captures:

| PCAP                | Total Packets | App Packets | Frame Bytes | TCP Bytes | App Bytes |
| ------------------- | ------------- | ----------- | ----------- | --------- | --------- |
| [pcap/tcpapp.pcap]  | 18            | 7           | 1283        | 596       | 75        |
| [pcap/webapp.pcap]  | 27            | 12          | 5468        | 884       | 3666      |
| [pcap/ajaxapp.pcap] | 27            | 12          | 4316        | 884       | 2514      |
| [pcap/sseapp.pcap]  | 21            | 8           | 3015        | 692       | 1609      |
| [pcap/wsapp.pcap]   | 34            | 12          | 4163        | 1104      | 1903      |

For more details on the meaning of the table column headings, see
section [Legend](#legend).


### Per Update Statistics

The table below shows the statistics for a single server-time update
requested by the client, i.e., this table shows the statistics for a
single request for server time sent by the client and the
corresponding response received.

| PCAP                | Total Packets | App Packets  | Frame Bytes | TCP Bytes    | App Bytes |
| ------------------- | ------------- | ------------ | ----------- | ------------ | --------- |
| [pcap/tcpapp.pcap]  | 3             | 2            | 213         | 96           | 15        |
| [pcap/webapp.pcap]  | 5             | 3            | 1253        | 160          | 923       |
| [pcap/ajaxapp.pcap] | 5             | 3            | 745         | 160          | 415       |
| [pcap/sseapp.pcap]  | 2             | 1            | 166         | 64           | 34        |
| [pcap/wsapp.pcap]   | 3             | 2            | 234         | 96           | 36        |

For more details on the meaning of the table column headings, see the
next section. It is apparent that the WebSocket-based approach (see
4th row in the table) is more efficient in terms of network bandwidth
consumption than the dynamic web app or Ajax-based web app. This is so
because WebSockets have very small header data. While an HTTP payload
may have a few hundred bytes of HTTP headers, a WebSocket payload has
only a few bytes of header data.

Note that the statistics for SSE-based app looks slightly better than
that of WebSocket-based app because the SSE-based app does not include
any requests from client to server due to the unidirectional nature
of SSE. If we compare the statistics of TCP-based app, SSE-based app
and Websocket-based app for the data being sent only from server to
client, it looks like this:

| PCAP                | Total Packets | App Packets  | Frame Bytes | TCP Bytes    | App Bytes |
| ------------------- | ------------- | ------------ | ----------- | ------------ | --------- |
| [pcap/tcpapp.pcap]  | 2             | 1            | 142         | 64           | 10        |
| [pcap/sseapp.pcap]  | 2             | 1            | 166         | 64           | 34        |
| [pcap/wsapp.pcap]   | 2             | 1            | 154         | 64           | 22        |

We don't include dynamic web app and Ajax-based app in the above table
because there is no way for these applications to send messages to a
client in a unidirectional manner. A dynamic web app and an Ajax-based
app can only send a response after a client has sent a request.
However, it is possible for TCP-based app, SSE-based app, and
Websocket-based app to send messages to a client in an already
established socket, event-stream, and websocket, respectively, without
the client having to request them.


### Legend

Here is a brief description of the column headings in the tables above:

  - Total Packets: Total number of packets.
  - App Packets: Number of only those packets that include application
    layer protocol data.
  - Frame Bytes: Total bytes found in frames.
  - TCP Bytes: Bytes found only in TCP headers.
  - App Bytes: Bytes found only in application layer payloads.

Note that Frame Bytes = 34 * Total Packets + TCP Bytes + App Bytes.
The number 34 in this formula is the sum of the length of the ethernet
header and the length of the IPv4 header in each packet found in the
PCAP, i.e., 34 = 14 + 20.


Payloads
--------

The subsections of this section presents application layer payloads
extracted from the PCAP files in the [pcap] directory. After reading
this section, see the text files in the [pcap] directory too for more
data parsed out from the PCAP files.


### TCP Socket App Payloads

This section presents application layer payload extracted from
[pcap/tcpapp.pcap] captured while running [tcpapp.py].

```
Hello!
Server time: 09:31:35

time
09:31:45

time
09:31:55

time
09:32:05

```

In the above output, only `time` followed by a newline was sent by the
client to the server. All the remaining output was sent by the server
to client.


### Web App Payloads

This section presents application layer payload extracted from
[pcap/webapp.pcap] captured while running [webapp.py].

```html
GET / HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1

HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 435
Date: Sun, 06 Jun 2021 09:36:17 GMT

<!DOCTYPE html>
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
<p>Server time: <time>09:36:17</time></p>
<button id="button">Refresh page</button>
<script>
const button = document.getElementById('button')
button.onclick = function () {
  window.location.reload()
}
</script>
</body>
</html>
GET / HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0

HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 435
Date: Sun, 06 Jun 2021 09:36:27 GMT

<!DOCTYPE html>
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
<p>Server time: <time>09:36:27</time></p>
<button id="button">Refresh page</button>
<script>
const button = document.getElementById('button')
button.onclick = function () {
  window.location.reload()
}
</script>
</body>
</html>
GET / HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0

HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 435
Date: Sun, 06 Jun 2021 09:36:37 GMT

<!DOCTYPE html>
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
<p>Server time: <time>09:36:37</time></p>
<button id="button">Refresh page</button>
<script>
const button = document.getElementById('button')
button.onclick = function () {
  window.location.reload()
}
</script>
</body>
</html>
GET / HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0

HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 435
Date: Sun, 06 Jun 2021 09:36:47 GMT

<!DOCTYPE html>
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
<p>Server time: <time>09:36:47</time></p>
<button id="button">Refresh page</button>
<script>
const button = document.getElementById('button')
button.onclick = function () {
  window.location.reload()
}
</script>
</body>
</html>
```


### Ajax App Payloads

This section presents application layer payload extracted from
[pcap/ajaxapp.pcap] captured while running [ajaxapp.py].

```html
GET / HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1

HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 807
Date: Thu, 10 Jun 2021 08:04:13 GMT

<!DOCTYPE html>
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
<p>Server time: <time id="time">08:04:13</time></p>
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
      time.innerHTML = xhr.response.time
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
GET /time HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: */*
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://172.105.253.239:8000/

HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 20
Date: Thu, 10 Jun 2021 08:04:23 GMT

{"time":"08:04:23"}
GET /time HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: */*
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://172.105.253.239:8000/

HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 20
Date: Thu, 10 Jun 2021 08:04:33 GMT

{"time":"08:04:33"}
GET /time HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: */*
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://172.105.253.239:8000/

HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 20
Date: Thu, 10 Jun 2021 08:04:43 GMT

{"time":"08:04:43"}
```

### SSE App Payloads

```html
GET / HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1

HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 569
Date: Thu, 10 Jun 2021 11:42:04 GMT

<!DOCTYPE html>
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
<p>Server time: <time id="time">11:42:04</time></p>
<script>
const time = document.getElementById('time')
var eventSource = new EventSource('/time');
eventSource.onmessage = function (event) {
  time.innerHTML = JSON.parse(event.data).time
};
eventSource.onerror = function (event) {
  time.innerHTML = '[error]'
};
</script>
</body>
</html>
GET /time HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: text/event-stream
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://172.105.253.239:8000/
Pragma: no-cache
Cache-Control: no-cache

HTTP/1.1 200 OK
Content-Type: text/event-stream; charset=utf-8
Date: Thu, 10 Jun 2021 11:42:14 GMT
Transfer-Encoding: chunked

1c
data: {"time": "11:42:14"}


1c
data: {"time": "11:42:24"}


1c
data: {"time": "11:42:34"}


```


### WebSocket App Payloads

This section presents application layer payload extracted from
[pcap/wsapp.pcap] captured while running [wsapp.py].

The client creates two connections with the websocket app. Here is the
initial connection that loads the home page:

```html
GET / HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1

HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 719
Date: Sun, 06 Jun 2021 09:43:28 GMT

<!DOCTYPE html>
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
<p>Server time: <time id="time">09:43:28</time></p>
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
```

Then the JavaScript code executing in the home page creates another
connection to the web server and immediately upgrades the
communication protocol to WebSocket:

```
GET /time HTTP/1.1
Host: 172.105.253.239:8000
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
Accept: */*
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Sec-WebSocket-Version: 13
Origin: http://172.105.253.239:8000
Sec-WebSocket-Extensions: permessage-deflate
Sec-WebSocket-Key: W+pQUnxtfyImglCepUIxdw==
Connection: keep-alive, Upgrade
Pragma: no-cache
Cache-Control: no-cache
Upgrade: websocket

HTTP/1.1 101 Switching Protocols
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Accept: jvz8rJ0yJN/A4J0kiZQLiifpQO8=

..6
).Qh];BdDs..{"time": "09:43:38"}................{"time": "09:43:48"}....4...@...Y...{"time": "09:43:58"}.....b.2..
```

The last two lines in the output above show the payload data exchanged
over the WebSocket. The non-printable characters are displayed as dots
above. Here is a hex dump of this data:

```
C1: 81 88 36 0d 29 16 51 68 5d 3b 42 64 44 73                          ..6.).Qh];BdDs
S1: 81 14 7b 22 74 69 6d 65 22 3a 20 22 30 39 3a 34 33 3a 33 38 22 7d  ..{"time": "09:43:38"}
C2: 81 88 a2 f4 f0 d0 c5 91 84 fd d6 9d 9d b5                          ..............
S2: 81 14 7b 22 74 69 6d 65 22 3a 20 22 30 39 3a 34 33 3a 34 38 22 7d  ..{"time": "09:43:48"}
C3: 81 88 a6 91 34 fd c1 f4 40 d0 d2 f8 59 98                          ....4...@...Y.
S3: 81 14 7b 22 74 69 6d 65 22 3a 20 22 30 39 3a 34 33 3a 35 38 22 7d  ..{"time": "09:43:58"}
C4: 88 82 19 db 13 62 1a 32                                            .....b.2
S4: 88 00                                                              ..
```

Each line in the hex dump above represents a WebSocket frame. The
WebSocket frames labelled C1, C2, C3, and C4 were sent from client to
server. Payload data in all frames sent from client to server are
masked by a 32-bit masking key. That is why the payloads in these
frames appear to be gibberish. The frames labelled S1, S2, S3, and S4
were sent from server to client. These frames do not use masking, so
the payloads in these frames are easily readable.

Here is a brief explanation about how to decode C1:

  - The initial `81` is `10000001` in binary. It has two flags set.
    The first flag set indicates that the current frame is the final
    fragment in the message, i.e., the message is composed of one
    frame in this case. The second flag set indicates that it is a
    text frame.

  - The following `88` is `10001000` in binary. The first `1` bit
    indicates that the payload data is masked. The remaining bits
    indicates that the payload is 8 bytes in length.

  - The bytes `36 0d 29 16` contain the masking key.

  - The bytes `51 68 5d 3b 42 64 44 73` contain the masked payload. We
    can use the masking key to decode it like this:

    ```
    $ python3 -q
    >>> m = bytes([0x36, 0x0d, 0x29, 0x16])
    >>> p = bytes([0x51, 0x68, 0x5d, 0x3b, 0x42, 0x64, 0x44, 0x73])
    >>> s = ''
    >>> for i in range(len(p)): s += chr(p[i] ^ m[i % 4])
    ...
    >>> s
    'get-time'
    ```

The payloads in C2 and C3 similarly decode to `'get-time'`. Here is a
description of C4:

  - The initial `88` is `10001000` in binary. It has two flags set.
    The second flag set indicates that this is a "connection close"
    frame.

  - The following `82` is `10000010` in binary. It indicates that the
    payload data is masked and the payload length is 2.

  - The bytes `19 db 13 62` form the masking key.

  - The payload data `1a 32` decodes to `03 e9`. This is the integer
    1001 written in big-endian format. The integer 1001 is defined as
    the status code "going away" for the close frame. Here is an
    example of how this payload is decoded to obtain the status code:

    ```
    $ python3 -q
    >>> print(hex(0x1a ^ 0x19), hex(0x32 ^ 0xdb))
    0x3 0xe9
    >>> print(0x3e9)
    1001
    ```

Finally, S4 is also a "connection close" frame as indicated by the
initial `88` in it and the `00` following it just indicates that there
is no payload data in this frame.

See [RFC 6455: &sect;5.2] for more details on WebSocket frame format.


Thanks
------

Thanks to [Prasoon Dwivedi](https://github.com/mitprasoon) for
contributing [sseapp.py], i.e., the example program for server-side
events.


[RFC 6455: &sect;5.2]: https://datatracker.ietf.org/doc/html/rfc6455#section-5.2

[tcpapp.py]: tcpapp.py
[webapp.py]: webapp.py
[ajaxapp.py]: ajaxapp.py
[sseapp.py]: sseapp.py
[wsapp.py]: wsapp.py

[pcap]: pcap
[pcap/tcpapp.pcap]: pcap/tcpapp.pcap
[pcap/webapp.pcap]: pcap/webapp.pcap
[pcap/ajaxapp.pcap]: pcap/ajaxapp.pcap
[pcap/sseapp.pcap]: pcap/sseapp.pcap
[pcap/wsapp.pcap]: pcap/wsapp.py
