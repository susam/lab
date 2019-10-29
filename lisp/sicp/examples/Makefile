run:
	scheme --quiet --load $(FILE) --eval '(%exit)'

*.scm: FORCE
	@make run FILE=$@

FORCE:
