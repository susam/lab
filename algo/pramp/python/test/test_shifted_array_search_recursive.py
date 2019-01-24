import unittest

from shifted_array_search_recursive import (binary_search, find_pivot,
                                            shifted_arr_search)


class ShiftedArraySearchRecursiveTest(unittest.TestCase):
    def setUp(self):
        self._binary_search = binary_search
        self._find_pivot = find_pivot
        self._shifted_arr_search = shifted_arr_search

    def test_find_pivot_one(self):
        a = [1]
        self.assertEqual(self._find_pivot(a, 0, len(a) - 1), 0)

    def test_find_pivot_two_unshifted(self):
        a = [1, 2]
        self.assertEqual(self._find_pivot(a, 0, len(a) - 1), 0)

    def test_find_pivot_two_shifted(self):
        a = [2, 1]
        self.assertEqual(self._find_pivot(a, 0, len(a) - 1), 1)

    def test_find_pivot_three_unshifted(self):
        a = [1, 2, 3]
        self.assertEqual(self._find_pivot(a, 0, len(a) - 1), 0)

    def test_find_pivot_three_shifted_once(self):
        a = [3, 1, 2]
        self.assertEqual(self._find_pivot(a, 0, len(a) - 1), 1)

    def test_find_pivot_three_shifted_twice(self):
        a = [2, 3, 1]
        self.assertEqual(self._find_pivot(a, 0, len(a) - 1), 2)

    def test_find_pivot_many_unshifted(self):
        a = [1, 2, 3, 4, 5, 6]
        self.assertEqual(self._find_pivot(a, 0, len(a) - 1), 0)

    def test_find_pivot_many_shifted(self):
        a = [3, 4, 5, 6, 1, 2]
        self.assertEqual(self._find_pivot(a, 0, len(a) - 1), 4)

    def test_binary_search_one(self):
        a = [1]
        self.assertEqual(self._binary_search(a, 0, len(a) - 1, 1), 0)

    def test_binary_search_one_absent(self):
        a = [1]
        self.assertEqual(self._binary_search(a, 0, len(a) - 1, 2), -1)

    def test_binary_search_two(self):
        a = [1, 2]
        self.assertEqual(self._binary_search(a, 0, len(a) - 1, 1), 0)
        self.assertEqual(self._binary_search(a, 0, len(a) - 1, 2), 1)

    def test_binary_search_two_absent(self):
        a = [1, 2]
        self.assertEqual(self._binary_search(a, 0, len(a) - 1, 3), -1)

    def test_binary_search_many(self):
        a = [1, 2, 3, 4, 5]
        self.assertEqual(self._binary_search(a, 0, len(a) - 1, 3), 2)
        self.assertEqual(self._binary_search(a, 0, len(a) - 1, 2), 1)

    def test_binary_search_many_absent(self):
        a = [1, 2, 3, 4, 5]
        self.assertEqual(self._binary_search(a, 0, len(a) - 1, 6), -1)

    def test_shifted_arr_search(self):
        a = [9, 12, 17, 2, 4, 5]
        self.assertEqual(self._shifted_arr_search(a, 2), 3)
        self.assertEqual(self._shifted_arr_search(a, 12), 1)
