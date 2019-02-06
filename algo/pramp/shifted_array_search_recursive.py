# Find the index of an element in a sorted and rotated array of distinct
# integers.

# Complexity: O(log n) time. O(log n) space.

# Note: The pivot finding algorithm here works only if the array has
# distinct integers. If there are duplicates, then the pivot finding
# algorithm cannot decide whether to search left or search right in test
# cases like: [2, 2, 2, 2, 1, 2] and [2, 1, 2, 2, 2, 2].


def shifted_arr_search(arr, num):
    pivot = find_pivot(arr, 0, len(arr) - 1)

    if pivot == 0 or arr[0] > num:
        return binary_search(arr, pivot, len(arr) - 1, num)
    else:
        return binary_search(arr, 0, pivot - 1, num)


# Find the index of the smallest element in a sorted and rotated array.
def find_pivot(arr, low, high):
    # This condition occurs only if the sorted array is unrotated.
    if low > high:
        return low

    mid = (low + high) // 2

    # Check if the middle element is the smallest element.
    if mid >= 1 and arr[mid] < arr[mid - 1]:
        return mid

    # Check if the smallest number lies in the left or right half.
    if arr[mid] > arr[high]:
        return find_pivot(arr, mid + 1, high)
    else:
        return find_pivot(arr, low, mid - 1)


# Find an element in a sorted array using binary search.
def binary_search(arr, low, high, num):
    if low > high:
        return -1

    mid = (low + high) // 2

    if num < arr[mid]:
        return binary_search(arr, low, mid - 1, num)
    elif num > arr[mid]:
        return binary_search(arr, mid + 1, high, num)
    else:
        return mid
