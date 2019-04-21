01-hello:
	make open FILE=$@.html
	
02-create-react-app: FORCE
	npx create-react-app $@; :
	cd $@ && npm start

03-hello-app: FORCE
	diff -x node_modules -ru 02-create-react-app/ 03-hello-app/ | vim -R -
	cd $@ && npm start

04-components: FORCE
	cd $@ && npm start

open:
	if command -v xdg-open > /dev/null; then \
	    xdg-open "$(FILE)"; \
	elif command -v open > /dev/null; then \
	    open "$(FILE)"; \
	else \
	    echo Cannot find xdg-open or open.; \
	fi

FORCE:
