From Sockets to WebSockets
==========================

This directory contains some experimental code that allows us to see
plain TCP socket, a simple HTTP application, an AJAX-based
application, and a WebSocket-based application in action and study the
properties of the application layer payloads that are exchanged while
each application is running and compare them against each other.

All code here is minimal in nature. No encryption is used. There is no
or very little error handling. The objective here is limited to
comparing only the application layer payloads resulting from the
various programs.


Contents
--------
 * [Get Started](#get-started)
 * [Setup](#setup)
 * [TCP Socket App](#simple-tcp-socket-app)
 * [Web App](#simple-web-app)
 * [Ajax App](#ajax-app)
 * [Websocket App](#websocket-app)

Get Started
-----------

If you only want to see what the payloads look like for each example
application, see the [pcaps](pcaps) folder that contain all the packet
captures corresponding to each example application. A summarized view
of these packet captures is provided in section [PCAP
Summary](#pcap-summary).

If you want to run the example programs on your system, continue
reading with the next section.


Setup
-----

Perform the following steps to set up a virtual Python environment to
run the example programs:

 1. The environment for experimentation depends on these tools: Git,
    Python 3, Netcat, a modern web browser. On a recent version of
    macOS (e.g., macOS Catalina 10.15), these tools are available by
    default. In case these tools are missing on your system or if you
    want recent versions of these tools, on macOS you may install them
    using [Homebrew](https://brew.sh/) with this command:

    ```sh
    brew install git python netcat
    ```

    On Debian, Ubuntu, or a similar system, you may install them with
    this command:

    ```sh
    brew install git python3 netcat
    ```

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
    websocket-based server time service:

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


TCP Socket App
--------------

Perform the following steps to run the simple TCP socket app
[tcpapp.py](tcpapp.py) and interact with it:


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

    $
    ```


Web App
-------

Perform the following steps to run the simple web app
[webapp.py](webapp.py) and interact with it:

  1. Enter the following command to run the simple web app server
     program:

     ```
     python3 webapp.py
     ```

  2. Visit http://localhost:8000/ with a web browser. A web page with
     the current time should appear.

  3. Click the "Refresh page" button. Updated time should appear.


Ajax App
--------

Perform the following steps to run the Ajax-based app
[ajaxapp.py](ajaxapp.py) and interact with it:

  1. Enter the following command to run the simple web app server
     program:

     ```
     python3 ajaxapp.py
     ```

  2. Visit http://localhost:8000/ with a web browser. A web page with
     the current time should appear.

  3. Click the "Refresh with Ajax" button. Updated time should appear.


WebSocket App
-------------

Perform the following steps to run the WebSocket-based app
[wsapp.py](wsapp.py) and interact with it:

 1. Enter the following command:

    ```
    python3 wsapp.py
    ```

 2. Visit http://localhost:8000/ with a web browser. A web page with
    the current time should appear.

 3. Click the "Refresh via WebSocket" button. Updated time should
    appear.
