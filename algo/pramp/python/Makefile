test: FORCE
	python3 -m unittest -vf

clean:
	find . -name "__pycache__" -exec rm -rf {} +
	find . -name "*.pyc" -exec rm -rf {} +

FORCE:

DeletionDistance \
:
	python3 -m unittest -vf test/test$@*.py
