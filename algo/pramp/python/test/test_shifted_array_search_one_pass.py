import unittest

from shifted_array_search_one_pass import shifted_arr_search


class ShiftedArraySearchRecursiveTest(unittest.TestCase):
    def test_find_pivot_one(self):
        a = [1]
        self.assertEqual(shifted_arr_search(a, 1), 0)
        self.assertEqual(shifted_arr_search(a, 2), -1)

    def test_find_pivot_two_unshifted(self):
        a = [1, 2]
        self.assertEqual(shifted_arr_search(a, 1), 0)
        self.assertEqual(shifted_arr_search(a, 2), 1)
        self.assertEqual(shifted_arr_search(a, 3), -1)

    def test_find_pivot_two_shifted(self):
        a = [2, 1]
        self.assertEqual(shifted_arr_search(a, 1), 1)
        self.assertEqual(shifted_arr_search(a, 2), 0)
        self.assertEqual(shifted_arr_search(a, 3), -1)

    def test_find_pivot_three_unshifted(self):
        a = [1, 2, 3]
        self.assertEqual(shifted_arr_search(a, 1), 0)
        self.assertEqual(shifted_arr_search(a, 2), 1)
        self.assertEqual(shifted_arr_search(a, 3), 2)
        self.assertEqual(shifted_arr_search(a, 4), -1)

    def test_find_pivot_three_shifted_once(self):
        a = [3, 1, 2]
        self.assertEqual(shifted_arr_search(a, 1), 1)
        self.assertEqual(shifted_arr_search(a, 2), 2)
        self.assertEqual(shifted_arr_search(a, 3), 0)
        self.assertEqual(shifted_arr_search(a, 4), -1)

    def test_find_pivot_three_shifted_twice(self):
        a = [2, 3, 1]
        self.assertEqual(shifted_arr_search(a, 1), 2)
        self.assertEqual(shifted_arr_search(a, 2), 0)
        self.assertEqual(shifted_arr_search(a, 3), 1)
        self.assertEqual(shifted_arr_search(a, 4), -1)

    def test_find_pivot_many_unshifted(self):
        a = [1, 2, 3, 4, 5, 6]
        self.assertEqual(shifted_arr_search(a, 1), 0)
        self.assertEqual(shifted_arr_search(a, 2), 1)
        self.assertEqual(shifted_arr_search(a, 3), 2)
        self.assertEqual(shifted_arr_search(a, 4), 3)
        self.assertEqual(shifted_arr_search(a, 5), 4)
        self.assertEqual(shifted_arr_search(a, 6), 5)
        self.assertEqual(shifted_arr_search(a, 7), -1)

    def test_find_pivot_many_shifted(self):
        a = [3, 4, 5, 6, 1, 2]
        self.assertEqual(shifted_arr_search(a, 1), 4)
        self.assertEqual(shifted_arr_search(a, 2), 5)
        self.assertEqual(shifted_arr_search(a, 3), 0)
        self.assertEqual(shifted_arr_search(a, 4), 1)
        self.assertEqual(shifted_arr_search(a, 5), 2)
        self.assertEqual(shifted_arr_search(a, 6), 3)
        self.assertEqual(shifted_arr_search(a, 7), -1)
