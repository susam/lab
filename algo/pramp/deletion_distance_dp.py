# Find the minimum number of characters to be deleted in two strings to
# get the same string.

# This solution optimizes the recursive solution in
# DeletionDistanceNaive.py using dynamic programming.

# Complexity: O(mn) time. O(mn) space.


def deletion_distance(a, b):
    m, n = len(a), len(b)

    # m x n matrix
    memo = [[0] * (n + 1) for row in range(m + 1)]

    for i in range(m + 1):
        for j in range(n + 1):
            if i == 0:
                memo[i][j] = j
            elif j == 0:
                memo[i][j] = i
            elif a[i - 1] == b[j - 1]:
                memo[i][j] = memo[i - 1][j - 1]
            else:
                memo[i][j] = 1 + min(memo[i - 1][j], memo[i][j - 1])

    return memo[m][n]


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
