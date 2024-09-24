VENV = ~/.venv/lispy

venv: FORCE
	rm -rf $(VENV)/
	python3 -m venv $(VENV)/
	$(VENV)/bin/pip3 install ruff mypy

lint:
	$(VENV)/bin/ruff check lispy
	$(VENV)/bin/ruff format --diff lispy
	$(VENV)/bin/mypy lispy

demo:
	./lispy ex/area.lisp

FORCE:
