# Find the minimum number of characters to be deleted in two strings to
# get the same string.

# This is a naive recursive solution.

# Complexity: O(2^n) time. O(n) space.

def deletion_distance(a, b):
    return deletionDistance(a, b, len(a), len(b))


def deletionDistance(a, b, m, n):
    if m == 0:
        return n

    if n == 0:
        return m

    if a[m - 1] == b[n - 1]:
        return deletionDistance(a, b, m - 1, n - 1)

    return 1 + min(deletionDistance(a, b, m - 1, n),
                   deletionDistance(a, b, m, n - 1))