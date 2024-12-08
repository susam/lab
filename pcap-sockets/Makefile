venv: FORCE

devdeps: venv
	. ./venv && pip3 install Flask==1.1.4 Flask-Sockets==0.2.1
	. ./venv && pip3 freeze > freeze.bkp

venv: FORCE
	rm -rf ~/.venv/websockets
	python3 -m venv ~/.venv/websockets
	echo . ~/.venv/websockets/bin/activate > venv

parsepcap:
	sh parsepcap.sh pcap/tcpapp.pcap > pcap/tcpapp.txt
	sh parsepcap.sh pcap/webapp.pcap > pcap/webapp.txt
	sh parsepcap.sh pcap/ajaxapp.pcap > pcap/ajaxapp.txt
	sh parsepcap.sh pcap/sseapp.pcap > pcap/sseapp.txt
	sh parsepcap.sh pcap/wsapp.pcap > pcap/wsapp.txt

FORCE:
