VENV = ~/.venv/lint

run: lint
	time python3 sha-prefix-embed.py

venv: FORCE
	rm -rf $(VENV)/
	python3 -m venv $(VENV)/
	$(VENV)/bin/pip3 install -U build twine
	$(VENV)/bin/pip3 install ruff mypy

lint:
	$(VENV)/bin/ruff check
	$(VENV)/bin/ruff format --diff
	$(VENV)/bin/mypy .

FORCE:
