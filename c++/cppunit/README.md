CppUnit Examples
================
This directory contains the following toy projects:

  - [minimal](minimal) - A tiny program in a single file that
    demonstrates a minimal way of using CppUnit.
  - [typical](typical) - A little more realistic project with multiple
    files that demonstrate how to have separate test source files for 
    separate test fixtures and the test runner.

To run these examples, first install CppUnit. On Mac, enter the
following command:

    brew install cppunit

On a Debian system, enter the following command:

    apt-get update && apt-get install libcppunit-dev

Enter the following command to run all the projects:

    make
