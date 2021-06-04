venv: FORCE

deps: venv
	. ./venv && pip3 install -r requirements.txt

devdeps: venv
	. ./venv && pip3 install Flask==1.1.4 Flask-Sockets==0.2.1
	. ./venv && pip3 freeze > requirements.txt

venv: FORCE
	rm -rf ~/.venv/websockets
	python3 -m venv ~/.venv/websockets
	echo . ~/.venv/websockets/bin/activate > venv

FORCE:
