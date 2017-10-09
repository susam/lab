An example systemd unit
=======================
This is a minimal example that sets up a Python 2 program named `bar.py` as a
systemd service unit.

The `Makefile` contains two targets:

  - `install` to install the service.
  - `uninstall` to uninstall the service.

The Makefile has been written to work on both CentOS and Debian.

The `bar.py` script is quite simple. It just keeps looping in an
infinite loop and logs a message to `/var/log/bar/bar.log` every second.

The `bar` file contains the systemd unit definition. It is a minimal definition
that shows the minimum configuration necessary to define a service for a program.
