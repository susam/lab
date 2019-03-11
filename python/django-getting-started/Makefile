NX = NX=$$(printf '\nx'); NL=$${NX%x}
NL = $${NL}

venv: FORCE
	python3 -m venv ~/.venv/django-getting-started
	echo . ~/.venv/django-getting-started/bin/activate > venv
	. ./venv && pip3 install django

# Default project.
create-01-foo: clean 
	rm -rf 01-foo
	. ./venv && django-admin startproject foo
	mv foo 01-foo

01-foo: clean
	if [ ! -d "$@" ]; then make create-"$@"; fi
	. ./venv && python3 01-foo/manage.py runserver

# Another default project.
create-02-foo: clean
	rm -rf 02-foo
	. ./venv && django-admin startproject foo
	mv foo 02-foo

02-foo: clean
	if [ ! -d "$@" ]; then make create-"$@"; fi
	git diff --no-index 01-foo 02-foo; :
	@echo
	# ------------------------------------
	# Note: Only SECRET_KEY differs above.
	# ------------------------------------
	@echo
	find 02-foo -type f

# Default app created with manage.py.
create-03-foo: clean
	rm -rf 03-foo
	. ./venv && django-admin startproject foo
	mv foo 03-foo
	. ./venv && cd 03-foo && python3 manage.py startapp bar

03-foo: clean
	if [ ! -d "$@" ]; then make create-"$@"; fi
	git diff --no-index --diff-filter=a 01-foo/ 03-foo/; :
	@echo
	# ------------------------------------
	# Note: Only SECRET_KEY differs above.
	# ------------------------------------
	@echo
	find 03-foo -type f
	@echo
	# -------------------------------------------------
	# Note: There are additional files for "bar" above.
	# -------------------------------------------------
	@echo
	. ./venv && python3 03-foo/manage.py runserver

# Default app created with startapp.
create-04-foo: clean
	rm -rf 04-foo
	. ./venv && django-admin startproject foo
	mv foo 04-foo
	. ./venv && cd 04-foo && django-admin startapp bar

04-foo: clean
	if [ ! -d "$@" ]; then make create-"$@"; fi
	git diff --no-index 03-foo 04-foo; :
	@echo
	# ------------------------------------
	# Note: Only SECRET_KEY differs above.
	# ------------------------------------
	@echo

# App with route.
create-05-foo: clean
	rm -rf 05-foo
	. ./venv && django-admin startproject foo
	mv foo 05-foo
	. ./venv && cd 05-foo && python3 manage.py startapp bar
	#
	# Edit app's views.py
	echo >> 05-foo/bar/views.py
	echo "from django.http import HttpResponse" >> 05-foo/bar/views.py
	echo >> 05-foo/bar/views.py
	echo "def index(request):" >> 05-foo/bar/views.py
	echo "    return HttpResponse('hello, world')" >> 05-foo/bar/views.py
	#
	# Create app's urls.py
	echo "from django.urls import path" > 05-foo/bar/urls.py
	echo "from . import views" >> 05-foo/bar/urls.py
	echo >> 05-foo/bar/urls.py
	echo "urlpatterns = [" >> 05-foo/bar/urls.py
	echo "    path('', views.index, name='index')," >> 05-foo/bar/urls.py
	echo "]" >> 05-foo/bar/urls.py
	#
	# Edit project's urls.py.
	$(NX); \
	    sed -e "s/import path/&, include/" \
	        -e "/urlpatterns = /a\\\
		   $(NL)\ \ \ \ path('bar/', include('bar.urls')),$(NL)" \
	           05-foo/foo/urls.py > 05-foo/foo/urls.new
	mv 05-foo/foo/urls.new 05-foo/foo/urls.py

05-foo: clean
	if [ ! -d "$@" ]; then make create-"$@"; fi
	git diff --no-index 03-foo/ 05-foo/; :
	@echo
	@echo Press ENTER to run server.; read
	. ./venv && cd 05-foo && python3 manage.py runserver

# App with 

clean:
	find . -name "__pycache__" -exec rm -r {} +
	find . -name "*.pyc" -exec rm {} +
	find . -name "db.sqlite3" -exec rm {} +

FORCE:
