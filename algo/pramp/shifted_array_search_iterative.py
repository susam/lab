# Find the index of an element in a sorted and rotated array of distinct
# integers.

# Complexity: O(log n) time, O(1) space.


def shifted_arr_search(arr, num):
    pivot = find_pivot(arr, 0, len(arr) - 1)

    if pivot == 0 or arr[0] > num:
        return binary_search(arr, pivot, len(arr) - 1, num)
    else:
        return binary_search(arr, 0, pivot - 1, num)


# Find the index of the smallest element in a sorted and rotated array.
def find_pivot(arr, low, high):
    while low <= high:
        mid = (low + high) // 2

        if mid >= 1 and arr[mid] < arr[mid - 1]:
            return mid

        if arr[mid] > arr[high]:
            low = mid + 1
        else:
            high = mid - 1

    return 0


# Find an element in a sorted array using binary search.
def binary_search(arr, low, high, num):
    while low <= high:
        mid = (low + high) // 2

        if num < arr[mid]:
            high = mid - 1
        elif num > arr[mid]:
            low = mid + 1
        else:
            return mid

    return -1


def main():
    print('find_pivot')
    print('==========')
    print()
    test_find_pivot([1], 0)
    test_find_pivot([1, 2], 0)
    test_find_pivot([2, 1], 1)
    test_find_pivot([1, 2, 3], 0)
    test_find_pivot([3, 1, 2], 1)
    test_find_pivot([2, 3, 1], 2)
    test_find_pivot([1, 2, 3, 4, 5, 6], 0)
    test_find_pivot([3, 4, 5, 6, 1, 2], 4)
    print()

    print('binary_search')
    print('=============')
    print()
    test_binary_search([1], 1, 0)
    test_binary_search([1], 2, -1)
    test_binary_search([1, 2], 1, 0)
    test_binary_search([1, 2], 2, 1)
    test_binary_search([1, 2], 3, -1)
    test_binary_search([1, 2, 3, 4, 5], 2, 1)
    test_binary_search([1, 2, 3, 4, 5], 3, 2)
    test_binary_search([1, 2, 3, 4, 5], 6, -1)
    test_binary_search([1, 2, 3, 4, 5], 6, -1)
    print()

    print('shifted_arr_search')
    print('==================')
    test([9, 12, 17, 2, 4, 5], 2, 3)
    test([9, 12, 17, 2, 4, 5], 12, 1)
    print()


def test_find_pivot(arr, expected):
    print('Input:    {}'.format(arr))

    output = find_pivot(arr, 0, len(arr) - 1)

    print('Output:   {}'.format(output))
    print('Expected: {}'.format(expected))
    print('-----')

    if output != expected:
        import sys
        sys.exit('TEST FAILURE!')


def test_binary_search(arr, num, expected):
    print('Input:    {}'.format(arr))

    output = binary_search(arr, 0, len(arr) - 1, num)

    print('Output:   {}'.format(output))
    print('Expected: {}'.format(expected))
    print('-----')

    if output != expected:
        import sys
        sys.exit('TEST FAILURE!')


def test(arr, num, expected):
    print('Input:    {}, {}'.format(arr, num))

    output = shifted_arr_search(arr, num)

    print('Output:   {}'.format(output))
    print('Expected: {}'.format(expected))
    print('-----')

    if output != expected:
        import sys
        sys.exit('TEST FAILURE!')


if __name__ == '__main__':
    main()
