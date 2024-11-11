install:
	# Install scripts.
	cp foo /etc/init.d/foo
	cp foo.py /usr/local/bin
	mkdir -p /var/log/foo
	chmod 755 /usr/local/bin/foo.py /etc/init.d/foo
	# Create user.
	if [ -e /etc/debian_version ]; then adduser --system --home / foo; fi
	if [ -e /etc/redhat-release ]; then useradd -r -d / -s /bin/false foo; fi
	chown foo /var/log/foo
	# Register service to start automatically.
	if [ -e /etc/debian_version ]; then update-rc.d foo defaults; fi
	if [ -e /etc/redhat-release ]; then chkconfig --add foo; fi

uninstall:
	# Deregister service.
	-service foo stop
	-if [ -e /etc/debian_version ]; then update-rc.d foo remove; fi
	-if [ -e /etc/redhat-release ]; then chkconfig --del foo; fi
	# Remove user.
	-if [ -e /etc/debian_version ]; then deluser foo; fi
	-if [ -e /etc/redhat-release ]; then userdel foo; fi
	# Uninstall scripts.
	rm -f /usr/local/bin/foo.py /etc/init.d/foo
