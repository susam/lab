An example sysvinit script
==========================
This is a tiny example that sets up a Python 2 program named `foo.py` as
a service.

The `Makefile` contains two targets:

  - `install` to install the service.
  - `uninstall` to uninstall the service.

The Makefile has been written to work on both CentOS and Debian.

The `foo.py` script is quite simple. It just keeps looping in an
infinite loop and logs a message to `/var/log/foo/foo.log` every second.

Here is a brief description of the `foo` script which is the actual
SysVInit script that gets installed into `/etc/init.d/foo`.

One of the goals in writing this example was to be as distro-independent
as possible, i.e. not rely on any features or quirks of a particular
distribution and rely on commands or features specified in POSIX as much
as possible.

Here are a few points about why certain things in this init script are
the way they are.

  - In the `start` function, we use the `-s /bin/sh` option to ensure
    that we can run the service with a user which does not have a valid
    shell set in `/etc/passwd`.

  - In the `running` function, we use the `ps` command instead of
    `kill -s 0` to check if the process because `kill` cannot send
    signals to a process the user does not have permission to. Using the
    `ps` command instead allows any user to check the status of the
    service.

  - The LSB init stanza (the `INIT INFO` block) at the top of the file
    is necessary only in CentOS for `chkconfig` to work correctly.
    Without this block, the following error would occur.

        $ sudo chkconfig --add foo
        service foo does not support chkconfig 

    An alternative on CentOS could be to add the following comment
    instead of the LSB init stanza.

        # chkconfig: 2345 20 80

    This works fine on CentOS. On Debian, this is ignored. Although
    Debian adds the symbolic links for the service in `/etc/rc*.d/` even
    if the LSB init stanza is missing, it does so with the following
    warning.

        $ sudo update-rc.d foo defaults
        insserv: warning: script 'foo' missing LSB tags and overrides

    Therefore, we have the LSB init stanza at the top of the file
    because it is understood by both `chkconfig` and `update-rc.d`.
