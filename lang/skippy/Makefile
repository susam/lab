VENV = ~/.venv/skippy

venv: FORCE
	rm -rf $(VENV)/
	python3 -m venv $(VENV)/
	$(VENV)/bin/pip3 install ruff mypy pytest

test:
	ln -sf skippy skippy.py
	$(VENV)/bin/pytest -vv
	rm -f skippy.py

lint:
	$(VENV)/bin/ruff check skippy
	$(VENV)/bin/ruff format --diff skippy
	$(VENV)/bin/mypy skippy

repl:
	./skippy

demo:
	./skippy ex/area.lisp

FORCE:
