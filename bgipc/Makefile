01-fork:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

02-parent-exits-first:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out &
	sleep 1
	# Both parent and child are running.
	ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Parent exits. Child is reassigned to PPID 1.
	ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Child exits.
	-ps -ef | grep "a\.out" | grep -v grep

03-zombie-no-wait:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out &
	sleep 1
	# Both parent and child are running.
	ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Child exits. Child appears as zombie.
	ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Parent exits. Child also disappears.
	-ps -ef | grep "a\.out" | grep -v grep

04-zombie-wait:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out &
	sleep 1
	# Both parent and child are running.
	ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Child exits. Child appears as zombie.
	ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Parent has waited. Child disappears.
	-ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Parent exits.
	-ps -ef | grep "a\.out" | grep -v grep

05-children-wait:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out &
	sleep 1
	# Both parent and child are running.
	ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# First child exits. First child appears as zombie.
	ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Parent has waited. First child disappears.
	-ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Second child exits. Second child appears as zombie.
	ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Parent has waited. Second child disappears.
	-ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Parent exits.
	-ps -ef | grep "a\.out" | grep -v grep

06-children-waitpid:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

07-wait-all:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

08-no-zombie-signal:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out &
	sleep 1
	# Both parent and child are running.
	ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Child exits. Child no longer appears as zombie.
	ps -ef | grep "a\.out" | grep -v grep
	sleep 2
	# Parent exits. Child also disappears.
	-ps -ef | grep "a\.out" | grep -v grep

09-signal-handler:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out &
	sleep 2
	# First SIGTERM is handled by the signal handler.
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill
	sleep 2
	# Second SIGTERM is not handled by the signal handler.
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill

10-sigaction:
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	#
	# Test 1: Send SIGINT to the program while it is already handling SIGINT.
	# Result: The second SIGINT is blocked until the first one is handled.
	./a.out &
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill -2
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill -2
	sleep 8
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill
	#
	# Test 2: Send SIGTERM to the program while it is already handling SIGINT.
	# Result: The second SIGINT is blocked until the first one is handled.
	./a.out &
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill -2
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill

11-sigaction-nodefer:
	# 200809L is required to use SA_NODEFER
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200809L $@.c
	#
	# Send SIGINT to the program.
	./a.out &
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill -2
	sleep 2
	#
	# Send another SIGINT to the program when the handler is sleeping.
	# The following occurs.
	#
	#   1. The sleep in the first invocation of the handler is interrupted.
	#   2. The signal handler is invoked the second time.
	#   3. The second invocation of the handler completes.
	#   4. The first handler resumes and completes.
	#   5. The program resumes.
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill -2
	sleep 8
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill

12-sigaction-mask:
	#
	# Test 1: Send SIGTERM when the handler is not blocking SIGTERM.
	# Result: The handler terminates.
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out 0 &
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill -2
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill
	sleep 3
	#
	# Test 2: Send SIGTERM when the handler is blocking SIGTERM.
	# Result: The handler completes and then the program terminates.
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200112L $@.c
	./a.out 1 &
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill -2
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill
	sleep 3

13-sigaction-restart:
	# 200809L is required to use SA_RESTART
	gcc -std=c99 -pedantic -Wall -Wextra -D_POSIX_C_SOURCE=200809L $@.c
	# Run ./a.out 0 manually, enter some input and press Ctrl+C.
	# Then run ./a.out 1 manually, enter some input, press Ctrl+C and
	# enter input again.

14-volatile:
	#
	# Test 1: int variable
	gcc -std=c99 -pedantic -Wall -Wextra -O1 -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill -s USR1
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill -s USR1
	# The program is an infinite loop despite two SIGUSR1 signals.
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill
	#
	# Test 2: volatile int variable 
	gcc -std=c99 -pedantic -Wall -Wextra -O1 -DVOLATILE -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill -s USR1
	sleep 2
	#
	# Test 3: volatile sigatomic_t variable
	gcc -std=c99 -pedantic -Wall -Wextra -O1 -DSIGATOMIC -D_POSIX_C_SOURCE=200112L $@.c
	./a.out &
	sleep 2
	ps -e -o pid,comm | grep " a\.out$$" | awk '{print $$1}' | xargs kill -s USR1
	sleep 2
	
15-pipe:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

16-fork-pipe:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

17-fork-two-pipes:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

18-ls-wc-pipe:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

19-fifo-write:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE $@.c
	rm -f fifo
	#
	# Test 1: Writer starts before shell reader. The writer's open()
	# blocks until the sed command is executed.
	./a.out &
	sleep 6 
	sed 's/^/sed: /' fifo
	#
	# Test 2: Writer starts after shell reader. The reader has to wait
	# until the writer sends messages.
	./a.out &
	sleep 2
	sed 's/^/sed: /' fifo
	#
	# Test 3: Three shell readers: Each message is received by exactly
	# one arbitrary reader.
	./a.out &
	sleep 2
	sed 's/^/sed 1: /' fifo &
	sed 's/^/sed 2: /' fifo &
	sed 's/^/sed 3: /' fifo
	#
	# Test 4: Check the permissions on the fifo file.
	umask
	umask -S
	ls -l fifo
	
20-fifo-read:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE 19-fifo-write.c -o fifo-write
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE $@.c -o fifo-read
	rm -f fifo
	#
	# Test 1: Reader starts before shell writer. The reader's open()
	# blocks until the writer starts writing to FIFO.
	./fifo-read 0 &
	sleep 6
	(echo shell: hello 1; sleep 1; echo shell: hello 2) > fifo
	sleep 4
	#
	# Test 2: Reader starts after shell writer. The shell writer blocks
	# until read starts writing to FIFO.
	./fifo-read 0 &
	sleep 2
	(echo shell: hello 1; sleep 1; echo shell: hello 2) > fifo
	sleep 4
	#
	# Test 3: Multiple writers.
	#
	./fifo-read 0 &
	sleep 6
	echo shell: hello 1 > fifo
	echo shell: hello 2 > fifo
	sleep 4
	#
	# Test 4: Reader starts before writer. The reader's open() blocks
	# until the writer's open() returns.
	./fifo-read 0 &
	sleep 6
	./fifo-write
	#
	# Test 5: Writer starts before reader. The writer's open() blocks
	# until the reader's open() returns.
	./fifo-write &
	sleep 6
	./fifo-read 0
	#
	# Test 6: Reader breaks while writer is writing. Writer exits with
	# exit status 141 (SIGPIPE) on the next write().
	(./fifo-write; echo Exit Status: $$?) &
	sleep 6
	./fifo-read 1

21-fifo-write-ndelay:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE $@.c
	rm -f fifo
	./a.out &
	sleep 2
	cat fifo

22-fifo-read-ndelay:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE $@.c
	rm -f fifo
	./a.out &
	sleep 2
	echo hello 1 > fifo
	sleep 1
	echo hello 2 > fifo
	sleep 1
	echo hello 3 > fifo
	sleep 1
	echo exit > fifo
	sleep 1

23-fcntl-setlkw:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	#
	# Test 1: Incompatible lock type and file open flag
	-./a.out w r
	-./a.out r w
	#
	# Test 2: Read lock
	./a.out r r &
	sleep 1
	./a.out r r &
	sleep 1
	./a.out w w
	#
	# Test 3: Write lock
	./a.out w w &
	sleep 1
	./a.out w w &
	sleep 1
	./a.out r r

24-fcntl-setlk:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out w w &
	sleep 2
	# The fcntl() call in the following invocation leads to the
	# following error because F_SETLK is used instead of F_SETLKW:
	# fcntl(): Resource temporarily unavailable
	-./a.out w w
	sleep 3
	./a.out w w

25-fcntl-getlk:
	gcc -std=c99 -pedantic -Wall -Wextra 24-fcntl-setlk.c -o lock-file
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	#
	# Test 1: Read Lock, Read Lock => Okay
	./lock-file r r &
	sleep 2
	./a.out r r
	#
	# Test 2: Read Lock, Write Lock => Conflict (Read Lock)
	./a.out w w
	sleep 3
	#
	# Test 3: Write Lock, Read Lock =>  Conflict (Write Lock)
	./lock-file w w &
	sleep 2
	./a.out r r
	#
	# Test 4: Write Lock, Write Lock =>  Conflict (Write Lock)
	./a.out w w
	sleep 3
	#
	# Test 5: No Lock, Read Lock => Okay
	./a.out r r
	#
	# Test 6: No Lock, Write Lock => Okay
	./a.out w w
	#
	# Test 7: Incompatible lock type and file open flag => Okay
	./a.out r w
	./a.out w r

26-fcntl-offset:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	rm -f lock
	dd if=/dev/zero of=lock bs=100 count=1
	./a.out r 0 10 &
	sleep 1
	./a.out r 0 10 &
	sleep 1
	-./a.out w 5 10
	-./a.out w 9 1
	./a.out w 10 10

27-msgsnd:
	touch /tmp/msgkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE $@.c -o msgsnd
	./msgsnd
	ipcs -q

28-msgrcv:
	# -----------------------------------------
	# Run 27-msgsnd before running this target.
	# -----------------------------------------
	touch /tmp/msgkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE $@.c -o msgrcv
	./msgrcv
	ipcs -q

29-msgctl:
	# -----------------------------------------
	# Run 27-msgsnd before running this target.
	# -----------------------------------------
	touch /tmp/msgkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE $@.c -o msgctl
	./msgctl
	ipcs -q

30-msgrcv-msgsz:
	# -----------------------------------------
	# Run 27-msgsnd before running this target.
	# -----------------------------------------
	touch /tmp/msgkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE $@.c -o msgsz
	./msgsz
	ipcs -q

31-sem-init:
	touch /tmp/semkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE $@.c -o seminit
	./seminit
	ipcs -s | grep -E "key|$$(id -u -n)"

32-sem-lock:
	# -------------------------------------------
	# Run 31-sem-init before running this target.
	# -------------------------------------------
	touch /tmp/semkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE $@.c -o semlock
	ipcs -s | grep -E "key|$$(id -u -n)"
	# Allocate resources
	./semlock 10 10 10 10 10 &
	sleep 2
	# Consume resources
	./semlock 5 -1 -2 -3 -4 &
	# Consume more resources
	./semlock 5 -9 -8 -7 -7 
	sleep 4

33-sem-rm:
	# -------------------------------------------
	# Run 31-sem-init before running this target.
	# -------------------------------------------
	touch /tmp/semkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE $@.c -o semrm
	./semrm
	ipcs -s | grep -E "key|$$(id -u -n)"

34-sem-safe-init:
	touch /tmp/semkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE $@.c -o semsafeinit
	./semsafeinit &
	sleep 2
	./semsafeinit
	ipcs -s | grep -E "key|$$(id -u -n)"

35-shm-write:
	touch /tmp/shmkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE $@.c -o shmwrite
	./shmwrite

36-shm-read:
	touch /tmp/shmkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE 35-shm-write.c -o shmwrite
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE $@.c -o shmread
	./shmwrite &
	sleep 1
	./shmread

37-shm-detach:
	touch /tmp/shmkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE $@.c -o shmdetach
	#
	# Test 1: Exit without detaching.
	# Result: nattch becomes 0 as soon as process exits. shm is not deleted.
	./shmdetach 0 &
	sleep 2
	# nattch = 1 after shmat().
	ipcs -m | grep -E "bytes|100"
	sleep 4
	# nattch = 0 after exit.
	ipcs -m | grep -E "bytes|100"
	#
	# Test 2: Delete, detach and exit.
	# Result: shm is deleted only after detach.
	./shmdetach 1 &
	sleep 2
	# nattch = 1 after shmat().
	ipcs -m | grep -E "bytes|100"
	sleep 4
	# shm is intact even after shmctl(IPC_RMID).
	ipcs -m | grep -E "bytes|100"
	sleep 4
	# shm is deleted after shmdt().
	ipcs -m | grep -E "bytes|100"
	sleep 4

38-shm-volatile:
	touch /tmp/shmkey
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE 35-shm-write.c -o shmwrite
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE -O1 $@.c -o shmvolatile
	./shmwrite &
	sleep 1
	./shmvolatile &
	# shmvolatile loops infinitely due to optimization.
	sleep 10 
	ps -e -o pid,comm | grep " shmvolatile$$" | awk '{print $$1}' | xargs kill
	#
	# Test 2: volatile int variable 
	gcc -std=c99 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE -O1 -DVOLATILE $@.c -o shmvolatile
	./shmwrite &
	sleep 1
	./shmvolatile

39-mmap:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE $@.c
	#
	# Test 1: Zero byte file
	: > /tmp/foo.txt
	-./a.out
	#
	# Test 2: One byte file
	printf A > /tmp/foo.txt
	./a.out

40-mmap-offset:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE $@.c
	truncate -s $$(getconf PAGESIZE) /tmp/foo.txt
	printf ABC >> /tmp/foo.txt
	./a.out

41-mmap-rw:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE $@.c
	printf ABC > /tmp/foo.txt
	./a.out &
	sleep 2
	cat /tmp/foo.txt; echo
	sleep 4
	cat /tmp/foo.txt; echo

42-munmap:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE $@.c
	printf ABC > /tmp/foo.txt
	-./a.out

43-mmap-file-change:
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE $@.c
	#
	# Test 1: Change file while the file is mapped.
	# Result: The changed file is visible to the program.
	# Result: Changes by program are also written to the file.
	printf ABC > /tmp/foo.txt
	ls -li /tmp/foo.txt
	./a.out &
	sleep 2
	printf PQR > /tmp/foo.txt
	ls -li /tmp/foo.txt
	sleep 4
	cat /tmp/foo.txt; echo
	ls -li /tmp/foo.txt
	#
	# Test 2: Delete file that is mapped and create new file.
	# Result: The new file is not visible to the program.
	# Result: Changes by program are not written to the new file.
	printf ABC > /tmp/foo.txt
	ls -li /tmp/foo.txt
	./a.out &
	sleep 2
	rm /tmp/foo.txt
	printf PQR > /tmp/foo.txt
	ls -li /tmp/foo.txt
	sleep 4
	cat /tmp/foo.txt; echo
	ls -li /tmp/foo.txt

44-mmap-volatile:
	#
	# Test 1: non-volatile variable.
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE -O1 $@.c
	printf A > /tmp/foo.txt
	./a.out &
	sleep 1
	printf X > /tmp/foo.txt
	# program loops infinitely due to optimization.
	sleep 4 
	ps -e -o pid,comm | grep " a.out$$" | awk '{print $$1}' | xargs kill
	#
	# Test 2: volatile variable 
	gcc -std=c99 -pedantic -Wall -Wextra -D_BSD_SOURCE -O1 -DVOLATILE $@.c
	printf A > /tmp/foo.txt
	./a.out &
	sleep 1
	printf X > /tmp/foo.txt
	sleep 1

45-unix-server:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c -o unixserver
	# -------------------------------------------------------------
	# Execute 46-unix-client to run the server and client together.
	# -------------------------------------------------------------

46-unix-client: 45-unix-server
	gcc -std=c99 -pedantic -Wall -Wextra $@.c -o unixclient
	./unixserver &
	sleep 2
	./unixclient 0
	sleep 2
	./unixclient 1
	# Ensure unixserver does not exist
	ps -ef | grep "unixserver" | grep -v grep || return 0

47-socketpair:
	gcc -std=c99 -pedantic -Wall -Wextra $@.c
	./a.out

clean:
	rm -f *.out
	rm -f fifo-read fifo-write fifo
	rm -f lock lock-file
	rm -f msgsnd msgrcv msgctl msgsz
	rm -f seminit semlock semrm semsafeinit
	rm -f shmwrite shmread shmdetach shmvolatile
	rm -f unixclient unixserver
	rm -f /tmp/msgkey /tmp/semkey /tmp/shmkey
	rm -rf /tmp/foo.txt

# vim: noet
