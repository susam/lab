# Find the minimum number of characters to be deleted in two strings to
# get the same string.

# This is a naive recursive solution.

# Complexity: O(2^n) time. O(n) space.


def deletion_distance(a, b):
    return _deletion_distance(a, b, len(a), len(b))


def _deletion_distance(a, b, m, n):
    if m == 0:
        return n

    if n == 0:
        return m

    if a[m - 1] == b[n - 1]:
        return _deletion_distance(a, b, m - 1, n - 1)

    return 1 + min(_deletion_distance(a, b, m - 1, n),
                   _deletion_distance(a, b, m, n - 1))


def main():
    test('heat', 'hit', 3)
    test('dog', 'frog', 3);
    test('hot', 'plot', 3);
    test('ab', 'ba', 2);
    test('some', 'some', 0);
    test('some', 'thing', 9);
    test('hit', '', 3);
    test('', 'hit', 3);
    test('', '', 0);


def test(a, b, expected):
    print('Input:    {}, {}'.format(a, b))

    output = deletion_distance(a, b)

    print('Output:   {}'.format(output))
    print('Expected: {}'.format(expected))
    print('-----')

    if output != expected:
        import sys
        sys.exit('TEST FAILURE!')


if __name__ == '__main__':
    main()
