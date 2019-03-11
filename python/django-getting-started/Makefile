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

# App with 

clean:
	find . -name "__pycache__" -exec rm -r {} +
	find . -name "*.pyc" -exec rm {} +
	find . -name "db.sqlite3" -exec rm {} +

FORCE:
