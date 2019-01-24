from test.test_shifted_array_search_recursive import \
    ShiftedArraySearchRecursiveTest

from shifted_array_search_iterative import (binary_search, find_pivot,
                                            shifted_arr_search)


class ShiftedArraySearchIterativeTest(ShiftedArraySearchRecursiveTest):
    def setUp(self):
        self._binary_search = binary_search
        self._find_pivot = find_pivot
        self._shifted_arr_search = shifted_arr_search
