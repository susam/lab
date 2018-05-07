JUnit Examples for JUnit 3, 4, 5
================================
This directory contains example tests for JUnit versions 3.8.2, 4.12,
and 5.2.0.

Enter the following command to run all the examples:

    make download
    make test

See [Makefile](Makefile) for the commands that compile and run the
tests.

Note: As one can see in the `Makefile`, while running a test with
JUnit4, it is necessary to include Hamcrest in the `classpath`,
otherwise the following error occurs:

    Exception in thread "main" java.lang.NoClassDefFoundError: org/hamcrest/SelfDescribing
