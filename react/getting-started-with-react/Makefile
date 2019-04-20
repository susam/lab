02-create-react-app: FORCE
	npx create-react-app $@
	cd $@ && npm start

03-hello-app: FORCE
	diff -x node_modules -ru 02-create-react-app/ 03-hello-app/ | vim -R -
	-cd $@ && npm start

FORCE:
