NX = NX=$$(printf '\nx'); NL=$${NX%x}
NL = $${NL}

venv: FORCE
	python3 -m venv ~/.venv/django-getting-started
	echo . ~/.venv/django-getting-started/bin/activate > venv
	. ./venv && pip3 install django

# Default project.
create-01-startproject: clean 
	rm -rf 01-startproject
	. ./venv && django-admin startproject foo
	mv foo 01-startproject

01-startproject: clean
	if [ ! -d "$@" ]; then make create-"$@"; fi
	. ./venv && python3 01-startproject/manage.py runserver

# Another default project.
create-02-startproject: clean
	rm -rf 02-startproject
	. ./venv && django-admin startproject foo
	mv foo 02-startproject

02-startproject: clean
	if [ ! -d "$@" ]; then make create-"$@"; fi
	git diff --no-index 01-startproject 02-startproject; :
	@echo
	# ------------------------------------
	# Note: Only SECRET_KEY differs above.
	# ------------------------------------
	@echo
	find 02-startproject -type f

# Default app created with manage.py.
create-03-manage-startapp: clean
	rm -rf 03-manage-startapp
	. ./venv && django-admin startproject foo
	mv foo 03-manage-startapp
	. ./venv && cd 03-manage-startapp && python3 manage.py startapp bar

03-manage-startapp: clean
	if [ ! -d "$@" ]; then make create-"$@"; fi
	git diff --no-index --diff-filter=a 01-startproject/ 03-manage-startapp/; :
	@echo
	# ------------------------------------
	# Note: Only SECRET_KEY differs above.
	# ------------------------------------
	@echo
	find 03-manage-startapp -type f
	@echo
	# -------------------------------------------------
	# Note: There are additional files for "bar" above.
	# -------------------------------------------------
	@echo
	. ./venv && python3 03-manage-startapp/manage.py runserver

# Default app created with startapp.
create-04-django-admin-startapp: clean
	rm -rf 04-django-admin-startapp
	. ./venv && django-admin startproject foo
	mv foo 04-django-admin-startapp
	. ./venv && cd 04-django-admin-startapp && django-admin startapp bar

04-django-admin-startapp: clean
	if [ ! -d "$@" ]; then make create-"$@"; fi
	git diff --no-index 03-manage-startapp 04-django-admin-startapp; :
	@echo
	# ------------------------------------
	# Note: Only SECRET_KEY differs above.
	# ------------------------------------
	@echo

# App with route.
create-05-views-urls: clean
	rm -rf 05-views-urls
	. ./venv && django-admin startproject foo
	mv foo 05-views-urls
	. ./venv && cd 05-views-urls && python3 manage.py startapp bar
	#
	# Edit app's views.py
	echo >> 05-views-urls/bar/views.py
	echo "from django.http import HttpResponse" >> 05-views-urls/bar/views.py
	echo >> 05-views-urls/bar/views.py
	echo "def index(request):" >> 05-views-urls/bar/views.py
	echo "    return HttpResponse('hello, world')" >> 05-views-urls/bar/views.py
	#
	# Create app's urls.py
	echo "from django.urls import path" > 05-views-urls/bar/urls.py
	echo "from . import views" >> 05-views-urls/bar/urls.py
	echo >> 05-views-urls/bar/urls.py
	echo "urlpatterns = [" >> 05-views-urls/bar/urls.py
	echo "    path('', views.index, name='index')," >> 05-views-urls/bar/urls.py
	echo "]" >> 05-views-urls/bar/urls.py
	#
	# Edit project's urls.py.
	$(NX); \
	    sed -e "s/import path/&, include/" \
	        -e "/urlpatterns = \\[/a\\\
		   $(NL)\ \ \ \ path('bar/', include('bar.urls')),$(NL)" \
	           05-views-urls/foo/urls.py > 05-views-urls/foo/urls.new
	mv 05-views-urls/foo/urls.new 05-views-urls/foo/urls.py

05-views-urls: clean
	if [ ! -d "$@" ]; then make create-"$@"; fi
	git diff --no-index 03-manage-startapp/ 05-views-urls/; :
	@echo
	@echo Press ENTER to run server.; read
	. ./venv && cd 05-views-urls && python3 manage.py runserver

# Combination of project's path(route, include()) and app's path(route, view).
create-06-path-include: clean
	@echo
	@echo Press ENTER to remove and create project again.
	@echo Press Ctrl + C to abort.; read
	@echo
	rm -rf 06-path-include
	. ./venv && django-admin startproject foo
	mv foo 06-path-include
	. ./venv && cd 06-path-include && python3 manage.py startapp bar

06-path-include: clean
	if [ ! -d "$@" ]; then make create-"$@"; fi
	. ./venv && \
	    cd 06-path-include && \
	    python3 manage.py runserver 2> /dev/null &
	sleep 2
	#
	# ----------------------------------------------------------------
	# 'bar/' and 'view1'   match 'bar/view1'           => HTTP 200
	# 'bar/' and 'view2/'  match 'bar/view2/'          => HTTP 200
	# 'bar/' and '//view3' match 'bar//view3'          => HTTP 200
	# 'bar/' and 'view1'   does not match 'bar/view1/' => HTTP 404
	# 'bar/' and 'view2/'  does not match 'bar/view2'  => HTTP 301
	# 'bar/' and '/view3'  does not match 'bar/view3'  => HTTP 404
	# ----------------------------------------------------------------
	curl -sI http://localhost:8000/bar/view1  | head -n 1  # HTTP 200
	curl -sI http://localhost:8000/bar/view2/ | head -n 1  # HTTP 200
	curl -sI http://localhost:8000/bar//view3 | head -n 1  # HTTP 200
	curl -sI http://localhost:8000/bar/view1/ | head -n 1  # HTTP 404
	curl -sI http://localhost:8000/bar/view2  | head -n 1  # HTTP 301
	curl -sI http://localhost:8000/bar/view3  | head -n 1  # HTTP 404
	#
	# ----------------------------------------------------------------
	# path('bar/', include('bar.urls')) behaves the same as
	# path('baz/', include(bar.urls)).
	# ----------------------------------------------------------------
	curl -sI http://localhost:8000/baz/view1  | head -n 1  # HTTP 200
	curl -sI http://localhost:8000/baz/view2/ | head -n 1  # HTTP 200
	curl -sI http://localhost:8000/baz//view3 | head -n 1  # HTTP 200
	curl -sI http://localhost:8000/baz/view1/ | head -n 1  # HTTP 404
	curl -sI http://localhost:8000/baz/view2  | head -n 1  # HTTP 301
	curl -sI http://localhost:8000/baz/view3  | head -n 1  # HTTP 404
	#
	# ----------------------------------------------------------------
	# 'qux' and 'view1'  match 'quxview1'            => HTTP 200
	# 'qux' and 'view2/' match 'quxview2/'           => HTTP 200
	# 'qux' and '/view3' match 'qux/view3'           => HTTP 200
	# 'qux' and 'view1'  does not match 'qux/view1'  => HTTP 404
	# 'qux' and 'view2/' does not match 'qux/view2/' => HTTP 404
	# 'qux' and '/view3' does not match 'quxview3'   => HTTP 404
	# ----------------------------------------------------------------
	curl -sI http://localhost:8000/quxview1   | head -n 1  # HTTP 200
	curl -sI http://localhost:8000/quxview2/  | head -n 1  # HTTP 200
	curl -sI http://localhost:8000/qux/view3  | head -n 1  # HTTP 200
	curl -sI http://localhost:8000/qux/view1  | head -n 1  # HTTP 404
	curl -sI http://localhost:8000/qux/view2/ | head -n 1  # HTTP 404
	curl -sI http://localhost:8000/quxview3   | head -n 1  # HTTP 404
	#
	# ----------------------------------------------------------------
	# 'quux'  matches 'quux'         => HTTP 200
	# 'quuz/' matches 'quuz/'        => HTTP 200
	# 'quux' does not match 'quux/'  => HTTP 404
	# 'quuz/' does not match 'quuz'  => HTTP 301
	# ----------------------------------------------------------------
	curl -sI http://localhost:8000/quux  | head -n 1  # HTTP 200
	curl -sI http://localhost:8000/quuz/ | head -n 1  # HTTP 200
	curl -sI http://localhost:8000/quux/ | head -n 1  # HTTP 404
	curl -sI http://localhost:8000/quuz  | head -n 1  # HTTP 301
	#
	# ----------------------------------------------------------------
	# 'bar/' and 'view2/' does not match 'bar/view2'. Request to
	# 'bar/view2' redirects to '/bar/view2'. Likewise for 'quuz/'.
	# ----------------------------------------------------------------
	curl -sI http://localhost:8000/bar/view2 | grep 'HTTP\|Location'
	curl -sI http://localhost:8000/quuz      | grep 'HTTP\|Location'
	@echo
	sleep 2
	@echo
	@echo Press ENTER to kill server.
	@read
	ps -e -o pid,args | grep 'manage\.py runserver$$' | \
	    awk '{print $$1}' | xargs kill
	sleep 2

clean:
	find . -name "__pycache__" -exec rm -r {} +
	find . -name "*.pyc" -exec rm {} +
	find . -name "db.sqlite3" -exec rm {} +

FORCE:
