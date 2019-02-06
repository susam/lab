# Find indices of a pair of numbers in an array which sum to a given
# limit. Return [i, j] such that i > j. Return [] if no such pair
# exists.

# Complexity: O(n) time. O(n) space.

# Note: The function name is misspelled ("wights" instead of "weights")
# in the Pramp test suite.


def get_indices_of_item_wights(a, limit):
    index_map = {}

    for index, value in enumerate(a):
        complement_index = index_map.get(limit - value)
        if complement_index is None:
            index_map[value] = index
        else:
            return [index, complement_index]

    return []


def main():
    test([9], 9, [])
    test([4, 4], 8, [1, 0])
    test([5, 4], 8, [])
    test([4, 4, 1], 5, [2, 1])
    test([4, 6, 10, 15, 16], 21, [3, 1])


def test(a, b, expected):
    print('Input:    {}, {}'.format(a, b))

    output = get_indices_of_item_wights(a, b)

    print('Output:   {}'.format(output))
    print('Expected: {}'.format(expected))
    print('-----')

    if output != expected:
        import sys
        sys.exit('TEST FAILURE!')


if __name__ == '__main__':
    main()
