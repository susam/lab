import socket
import time


def main():
    port = 8000
    s = socket.socket()
    s.bind(('', port))
    s.listen()
    print('Listening on port', port, '...')
    while True:
        conn, addr = s.accept()
        print('Accepted connection from', addr)
        handle_client(conn)
        print('Closed connection from', addr)


def handle_client(conn):
    conn.sendall(b'Hello!\nServer time: ' +
                 formatted_time().encode() + b'\n\n')
    while True:
        data = conn.recv(1024)
        print('Received from client:', data)
        if data == b'time\n':
            conn.sendall(formatted_time().encode() + b'\n\n')
        elif data == b'bye\n':
            conn.sendall(b'Good bye!\n\n')
            conn.close()
            break
        elif data == b'':
            conn.close()
            break
        else:
            conn.sendall(b'I do not understand: ' + data + b'\n')
            pass


def formatted_time():
    return time.strftime('%H:%M:%S')


if __name__ == '__main__':
    main()
