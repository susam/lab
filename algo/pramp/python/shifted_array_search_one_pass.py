# Find the index of an element in a sorted and rotated array of distinct
# integers.

# Complexity: O(log n) time. O(1) space.


def shifted_arr_search(arr, num):
    return rotated_binary_search(arr, 0, len(arr) - 1, num)


def rotated_binary_search(arr, low, high, num):
    while low <= high:
        mid = (low + high) // 2

        if arr[mid] == num:
            return mid

        # If the lower half is sorted ...
        if arr[low] <= arr[mid]:
            # If the number lies in the lower half ...
            if arr[low] <= num <= arr[mid]:
                # Search the lower half in the next iteration ...
                high = mid - 1
            else:
                # Else search the upper half in the next iteration.
                low = mid + 1

        # Else the upper half must be sorted.
        else:
            # If the number lies in the upper half ...
            if arr[mid] <= num <= arr[high]:
                # Search the upper half in the next iteration ...
                low = mid + 1
            else:
                # Else search the lower half in the next iteration.
                high = mid - 1

    return -1
