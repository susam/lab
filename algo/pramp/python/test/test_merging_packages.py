import unittest

from merging_packages import get_indices_of_item_wights as f


class MergingPackagesTest(unittest.TestCase):
    def test_one_item(self):
        a = [9]
        self.assertEqual(f(a, 9), [])

    def test_two_items(self):
        a = [4, 4]
        self.assertEqual(f(a, 8), [1, 0])

    def test_two_items_none(self):
        a = [5, 4]
        self.assertEqual(f(a, 8), [])

    def test_duplicate_items(self):
        a = [4, 4, 1]
        self.assertEqual(f(a, 5), [2, 1])

    def test_many_items(self):
        a = [4, 6, 10, 15, 16]
        self.assertEqual(f(a, 21), [3, 1])
