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
