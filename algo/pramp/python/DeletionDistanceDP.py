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
