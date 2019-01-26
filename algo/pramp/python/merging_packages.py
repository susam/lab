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
