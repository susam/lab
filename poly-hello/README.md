Binary Size
===========
This directory contains a few "hello, world" programs. They are compiled
to binary executables or binary bytecodes in order to compare their
sizes.

Here are the results:

    8640    c-hello
    9128    cpp-hello
    1633717 go-hello
    256040  rust-hello
    416     Hello.class
    156     __pycache__/hello.cpython-35.pyc

As a bonus, here are the shared object dependencies required by each
binary:

    c-hello:
            linux-vdso.so.1 (0x00007ffd65b86000)
            libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f3c14718000)
            /lib64/ld-linux-x86-64.so.2 (0x000055a54612a000)
    cpp-hello:
            linux-vdso.so.1 (0x00007fff95bf8000)
            libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f1a184c9000)
            libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f1a181c5000)
            libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f1a17fae000)
            libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f1a17c0f000)
            /lib64/ld-linux-x86-64.so.2 (0x00005566f6271000)
    go-hello:
            not a dynamic executable
    rust-hello:
            linux-vdso.so.1 (0x00007ffceff8f000)
            libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007fc87e2fd000)
            librt.so.1 => /lib/x86_64-linux-gnu/librt.so.1 (0x00007fc87e0f5000)
            libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fc87ded8000)
            libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fc87dcc1000)
            libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fc87d922000)
            /lib64/ld-linux-x86-64.so.2 (0x000055facc583000)
