# Find the minimum number of characters to be deleted in two strings to
# get the same string.

# This solution optimizes the space complexity of the solution in
# DeletionDistanceDPO.py by keeping only those memo values that are
# required in each iteration and discarding unneeded memo values.

# Complexity: O(mn) time. O(min(m, n)) space.

def deletion_distance(a, b):
    m, n = len(a), len(b)

    # Ensure n <= m to reduce space complexity.
    if n > m:
        a, b = b, a
        m, n = n, m

    prevMemo = [0] * (n + 1)

    for i in range(m + 1):
        currMemo = [0] * (n + 1)

        for j in range(n + 1):
            if i == 0:
                currMemo[j] = j
            elif j == 0:
                currMemo[j] = i
            elif a[i - 1] == b[j - 1]:
                currMemo[j] = prevMemo[j - 1]
            else:
                currMemo[j] = 1 + min(prevMemo[j], currMemo[j - 1])

        prevMemo = currMemo

    return currMemo[n]
