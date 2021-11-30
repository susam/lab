# A vector of integers is represented by a list of pairs [n, v] where
# n represents the number of times v occurs in the vector.
#
# Example: [[2, 5], [3, 7]] represents the vector [5, 5, 7, 7, 7].
#
# Given two such representations of vectors a and b, compute the dot
# product of a and b.

# Complexity: O(n) time where n = max(len(a), len(b)). O(1) space.

def dot_product(a, b):
    COUNT, VALUE = 0, 1
    i = j = 0
    result = 0

    while i < len(a):
        common_count = min(a[i][COUNT], b[j][COUNT])
        result += common_count * a[i][VALUE] * b[j][VALUE]
        a[i][COUNT] -= common_count
        b[j][COUNT] -= common_count
        if a[i][COUNT] == 0:
            i += 1
        if b[j][COUNT] == 0:
            j += 1
    return result


def main():
    test([[3, 10], [2, 20], [1, 10]],
         [[2, 10], [4, 20]],
         1400)
    test([[10000, 5]],
         [[10000, 7]],
         350000)
    test([[900, 5]],
         [[500, 7], [400, 9]],
         35500)
    test([], [], 0)


def test(a, b, expected):
    print('Input:    {}, {}'.format(a, b))

    output = dot_product(a, b)

    print('Output:   {}'.format(output))
    print('Expected: {}'.format(expected))
    print('-----')

    if output != expected:
        import sys
        sys.exit('TEST FAILURE!')


if __name__ == '__main__':
    main()
