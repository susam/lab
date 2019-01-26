PROJECT = pramp

all: lint test coverage

venv: FORCE
	python3 -m venv ~/.venv/$(PROJECT)
	echo . ~/.venv/$(PROJECT)/bin/activate > venv
	. ./venv && pip3 install pylama coverage pylama-pylint

lint:
	. ./venv && isort --quiet --diff
	. ./venv && pylama

test: FORCE
	python3 -m unittest -vf

coverage:
	. ./venv && coverage run -m unittest -v
	. ./venv && coverage report --show-missing
	. ./venv && coverage html

clean:
	find . -name "__pycache__" -exec rm -rf {} +
	find . -name "*.pyc" -exec rm -rf {} +

FORCE:

deletion_distance \
merging_packages \
:
	python3 -m unittest -vf test/test_$@*.py
