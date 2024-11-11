01-htons:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

02-sockaddr:
	# _D_POSIX_C_SOURCE required for definition of getaddrinfo.
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out

03-pton:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

04-getaddrinfo:
	# _D_POSIX_C_SOURCE required for definition of getaddrinfo.
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out

05-getprotoent:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out

06-socket:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	sleep 2
	netstat -np | grep "a\.out"
	sleep 4 # Wait for program to exit.


07-bind-connect:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	sleep 2
	-netstat -np | grep "a\.out"
	sleep 4 # Wait for program to exit.

08-bind-listen:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	#
	# Test 1
	# ======
	# This test sends three messages at one second intervals so that it
	# leads to three separate recv() calls in the C program.
	./a.out &
	sleep 1
	-netstat -nap | grep 9090
	(echo msg1; sleep 1; echo msg2; sleep 1; echo msg3) | nc -vv localhost 9090
	-netstat -nap | grep 9090
	#
	# Sleep for more than 60 seconds so that the previous listening
	# socket in TIME_WAIT state clears.
	sleep 61
	#
	# Test 2
	# ======
	# This test sends a message and closes the connection after 2
	# seconds. As a result, the second recv() call returns 0 which is
	# interpreted by the C program as closed connection.
	./a.out &
	-netstat -nap | grep 9090
	echo msg1 | nc -vvw 2 localhost 9090
	-netstat -nap | grep 9090

09-error-address-already-in-use:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	#
	# Test 1
	# ======
	# The first time the program is run, it should successfully bind to
	# its listening port.
	./a.out &
	sleep 1
	nc -vv localhost 9090
	#
	# Test 2
	# ======
	# The second time the program is run, it should fail with
	# "Address already in use" error message.
	./a.out

10-so-reuseaddr:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	#
	# Test 1
	# ======
	# Program is killed before any connection.
	# No SO_REUSEADDR followed by no SO_REUSEADDR as well as SO_REUSEADDR.
	./a.out 0 &
	sleep 1
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill
	./a.out 1 &
	sleep 1
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill
	./a.out 0 &
	sleep 1
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill
	./a.out 1 &
	sleep 1
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill
	#
	# Test 2
	# ======
	# Program quits after connection.
	# No SO_REUSEADDR followed by no SO_REUSEADDR as well as SO_REUSEADDR.
	# Result: bind(): Address already in use for both cases.
	./a.out 0 &
	sleep 1
	nc -vv localhost 9090
	./a.out 0
	./a.out 1
	sleep 61
	#
	# Test 3
	# ======
	# Program quits after connection.
	# SO_REUSEADDR followed by no SO_REUSEADDR as well as SO_REUSEADDR.
	# Result: bind(): Address already in use for first case only.
	./a.out 1 &
	sleep 1
	nc -vv localhost 9090
	./a.out 0
	./a.out 1 &
	sleep 1
	nc -vv localhost 9090
	sleep 61

11-sendto \
12-dgram-connect:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	#
	# Test 1
	# ======
	# Send UDP datagrams and ensure that they are received on al
	# listening socket.
	nc -vvlup 9090 &
	sleep 1
	./a.out
	ps -e -o pid,comm | grep " nc$$" | awk '{print $$1}' | xargs kill
	#
	# Test 2
	# ======
	# Send UDP datagrams when there is no listening socket at the other
	# end. In this case, send() calls succeed but sendto() calls fail.
	# It seems the function that was called first succeeds. If sendto()
	# is called first, then sendto() calls succeed and send() calls fail.
	sleep 2
	./a.out

13-recvfrom:
	#
	# Test 1
	# ======
	# Send UDP datagrams to the listening socket.
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	-netstat -nap | grep 9090
	(echo msg1; sleep 1; echo msg2; sleep 1; echo msg3) | nc -vvuq 0 localhost 9090
	-netstat -nap | grep 9090
	#
	# Test 2
	# ======
	# Since the listening UDP socket does not enter TIME_WAIT state, the
	# second run of the program also binds successfully.
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	-netstat -nap | grep 9090
	(echo msg1; sleep 1; echo msg2; sleep 1; echo msg3) | nc -vvuq 0 localhost 9090
	-netstat -nap | grep 9090

14-client-shutdown-close:
	#
	# Test SHUT_RD
	# ============
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out 0 &
	(sleep 4; printf aa; sleep 6; printf bb; sleep 6; printf cc) | nc -vvlp 9090
	#
	# Test SHUT_RW
	# ============
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	(./a.out 1; echo Program Exit Status: $$?) &
	(sleep 4; printf aa) | nc -vvlp 9090; echo Netcat Exit Status: $$?
	sleep 4  # Wait for program to recv() and exit due to SIGPIPE on send().
	sleep 2  # Additional delay before next test.
	#
	# Test SHUT_RDRW
	# ==============
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	(./a.out 2; echo Program Exit Status: $$?) &
	(sleep 4; printf aa) | nc -vvlp 9090; echo Netcat Exit Status: $$?
	sleep 4  # Wait for program to recv() and exit due to SIGPIPE on send().
	sleep 2  # Additional delay before next test.
	#
	# Test close()
	# ============
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	(./a.out -1; echo Program Exit Status: $$?) &
	(sleep 4; printf aa) | nc -vvlp 9090; echo Netcat Exit Status: $$?
	sleep 12  # Wait for program to exit.
	sleep 2   # Additional delay before end.

15-server-shutdown-close:
	#
	# Test SHUT_RD
	# ============
	# Netcat 1: send()/recv() successful even after shutdown.
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out 0 &
	((sleep 2; printf aa; sleep 2; printf bb) | nc -vv localhost 9090; \
	 echo Netcat 1 Exit Status: $$?) &
	# Ensure Netcat 2 starts after Netcat 1 connects successfully.
	sleep 1
	# Netcat 2: Program accepts connection but closes it on shutdown().
	nc -vv localhost 9090; echo Netcat 2 Exit Status: $$?
	# Netcat 3: Program does not accept the connection.
	nc -vv localhost 9090; echo Netcat 3 Exit Status: $$?
	sleep 4 # Wait for program to exit.
	#
	# Test SHUT_RW
	# ============
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out 1 &
	((sleep 2; printf aa; sleep 2; printf bb) | nc -vv localhost 9090; \
	 echo Netcat 1 Exit Status: $$?) &
	sleep 1
	nc -vv localhost 9090; echo Netcat 2 Exit Status: $$?
	nc -vv localhost 9090; echo Netcat 3 Exit Status: $$?
	sleep 4 # Wait for program to exit.
	#
	# Test SHUT_RDRW
	# ==============
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out 1 &
	((sleep 2; printf aa; sleep 2; printf bb) | nc -vv localhost 9090; \
	 echo Netcat 1 Exit Status: $$?) &
	sleep 1
	nc -vv localhost 9090; echo Netcat 2 Exit Status: $$?
	nc -vv localhost 9090; echo Netcat 3 Exit Status: $$?
	sleep 4 # Wait for program to exit.
	# Test close()
	# ============
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out -1 &
	((sleep 2; printf aa; sleep 2; printf bb) | nc -vv localhost 9090; \
	 echo Netcat 1 Exit Status: $$?) &
	sleep 1
	nc -vv localhost 9090; echo Netcat 2 Exit Status: $$?
	nc -vv localhost 9090; echo Netcat 3 Exit Status: $$?
	sleep 4 # Wait for program to exit.

16-connection-shutdown-close:
	#
	# Test SHUT_RD
	# ============
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out 0 &
	sleep 2
	(printf aa; sleep 2; printf bb; sleep 4; printf cc) | nc -vv localhost 9090
	printf zz | nc -vv localhost 9090
	#
	# Test SHUT_RW
	# ============
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	(./a.out 1; echo Program Exit Status: $$?) &
	sleep 2
	printf aa | nc -vv localhost 9090; echo Netcat Exit Status: $$?
	#
	# Test SHUT_RDRW
	# ==============
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	(./a.out 2; echo Program Exit Status: $$?) &
	sleep 2
	printf aa | nc -vv localhost 9090; echo Netcat Exit Status: $$?
	#
	# Test close()
	# ============
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	(./a.out -1; echo Program Exit Status: $$?) &
	sleep 2
	(printf aa; sleep 2; printf bb; sleep 4; printf cc) | nc -vv localhost 9090; \
	echo Netcat 1 Exit Status: $$?
	printf zz | nc -vv localhost 9090; echo Netcat 2 Exit Status: $$?

17-getpeername:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out 0 &
	sleep 1
	printf aa | nc -vv localhost 9090

18-gethostname:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out 0

19-stream-server:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	#
	# Test 1: Simple test.
	echo aa | nc -vv localhost 9090
	echo bb | nc -vv localhost 9090
	echo cc | nc -vv localhost 9090
	#
	# Test 2: Simultaneous connections.
	(sleep 2; echo msg1) | nc -vv localhost 9090 &
	(sleep 2; echo msg2) | nc -vv localhost 9090 &
	(sleep 2; echo msg3) | nc -vv localhost 9090 &
	#
	# Kill server.
	sleep 4
	ps -ef | grep "a\.out" | grep -v grep
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill

20-stream-client:
	#
	# Test 1: Connect to netcat.
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	echo hello from netcat | nc -vvlp 9090 &
	sleep 2
	./a.out
	#
	# Test 2: Connect to our own server.
	mv a.out client.out
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L 19-stream-server.c
	mv a.out server.out
	./server.out &
	sleep 2
	./client.out
	sleep 2
	ps -e -o pid,comm | grep " server\.out$$" | awk '{print $$1}' | xargs kill

21-dgram-server:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	sleep 2
	(echo msg1; sleep 2; echo msg2) | nc -vvuq0 localhost 9090; \
	echo Netcat 1 Exit Status: $$?
	(echo msg3; sleep 2; echo exit) | nc -vvuq0 localhost 9090; \
	echo Netcat 2 Exit Status: $$?

22-dgram-client:
	#
	# Test 1: Connect to netcat.
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	echo hello from netcat | (nc -vvw2 -ulp 9090; echo Netcat Exit Status: $$?) &
	sleep 1
	./a.out
	sleep 4 # Wait for Netcat to exit.
	#
	# Test 2: Connect to our own server.
	mv a.out client.out
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L 21-dgram-server.c
	mv a.out server.out
	./server.out &
	sleep 2
	./client.out

23-nonblock-server:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	# Wait for the server to try accept() twice before connecting to it.
	sleep 8;
	# Wait for the server to try recv() twice before sending data.
	(sleep 5; echo hello from client) | nc -vv -q0 localhost 9090
	# Wait for the server to try recv() again and receive the data.
	sleep 4
	# Kill the server.
	ps -ef | grep "a\.out" | grep -v grep
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill

24-select-stdin:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	(sleep 1; echo foo; sleep 2; echo bar) | ./a.out

25-select-server:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	(echo hello 1; sleep 2; echo bye 1) | nc -vv -q0 localhost 9090 &
	(echo hello 2; sleep 4; echo bye 2) | nc -vv -q0 localhost 9090
	echo exit | nc -vv -q0 localhost 9090

26-sendall:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	nc -vv -lp 9090 &
	sleep 2
	./a.out

27-htonf:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

28-ieee754:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

29-pack:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

30-tiny-recv-buffer:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	echo msg1msg2msg3msg4 | nc -vv -l -p 9090 &
	sleep 2
	# The program makes three recv() calls. It reads only 4 bytes at a
	# time in each recv() call. On Linux, the first call receives only
	# the first 4 bytes and the next 4 bytes is received by the next
	# call. POSIX.1-2001 also seems to guarantee this behaviour:
	#
	# "For stream-based sockets, such as SOCK_STREAM, message boundaries
	# shall be ignored. In this case, data shall be returned to the user
	# as soon as it becomes available, and no data shall be discarded."
	./a.out

31-dgram-broadcast:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	nc -vvnulp 9090 &
	sleep 1
	./a.out
	ps -e -o pid,comm | grep " nc$$" | awk '{print $$1}' | xargs kill

32-gethostbyname:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE $@.c
	./a.out

33-gethostbyaddr:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE $@.c
	./a.out

34-getnameinfo:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out

35-aton:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE=200112L $@.c
	./a.out

36-backlog:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	sleep 2
	echo msg1 | nc -vv localhost 9090 &
	echo msg2 | nc -vv localhost 9090 &
	echo msg3 | nc -vv localhost 9090 &
	echo msg4 | nc -vv localhost 9090 &
	echo msg5 | nc -vv localhost 9090 &
	echo exit | nc -vv localhost 9090 &
	sleep 60

37-poll-stdin:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	(sleep 1; echo foo; sleep 2; echo bar) | ./a.out

38-poll-server:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	sleep 1
	echo msg1 | nc -vv -w5 localhost 9090 &
	echo msg2 | nc -vv -w5 localhost 9090 &
	echo msg3 | nc -vv -w5 localhost 9090 &
	echo msg4 | nc -vv -w5 localhost 9090 &
	echo msg5 | nc -vv -w5 localhost 9090 &
	echo exit | nc -vv -w5 localhost 9090 &
	sleep 15

clean:
	rm *.out

# vim: noet
