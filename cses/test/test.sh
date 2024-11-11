#!/bin/sh

set -e

# Input and expected result must not have any leading or trailing
# newlines. A trailing newline will be added to the input by this
# function before feeding it to the program being tested. Similarly, a
# trailing newline will be added to the expected result before
# comparing it with the actual output from the program.
check()
{
    printf 'input: %s ... ' $(printf '%s' "$1" | head -n 1)
    printf '%s\n' "$1" > input.txt
    printf '%s\n' "$2" > expected.txt
    ./a.out < input.txt > output.txt
    if diff=$(diff -u expected.txt output.txt)
    then
        printf 'pass\n'
    else
        printf 'fail\n'
        printf '%s\n' "$diff"
    fi
}

main()
{
    . test/"${1%.*}.sh"
    printf 'done\n'
}

main "$@"
