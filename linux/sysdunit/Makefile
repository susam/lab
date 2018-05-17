install:
	# Install scripts.
	cp bar.py /usr/local/bin
	cp bar.service /etc/systemd/system
	mkdir -p /var/log/bar
	chmod 755 /usr/local/bin/bar.py
	# Create user.
	if [ -e /etc/debian_version ]; then adduser --system --home / bar; fi
	if [ -e /etc/redhat-release ]; then useradd -r -d / -s /bin/false bar; fi
	chown bar /var/log/bar
	# Register service to start automatically.
	systemctl enable bar

uninstall:
	# Deregister service.
	-systemctl stop bar
	-systemctl disable bar
	# Remove user.
	-if [ -e /etc/debian_version ]; then deluser bar; fi
	-if [ -e /etc/redhat-release ]; then userdel bar; fi
	# Uninstall scripts.
	rm -f /usr/local/bin/bar.py
	# Remove data files.
	rm -rf /var/log/bar /var/run/bar.pid
