import unittest
from DeletionDistanceNaive import deletion_distance


class DeletionDistanceNaiveTest(unittest.TestCase):
    def setUp(self):
        self._f = deletion_distance

    def test_common_subsequence(self):
        self.assertEqual(self._f('heat', 'hit'), 3)

    def test_common_prefix(self):
        self.assertEqual(self._f('dog', 'frog'), 3)

    def test_common_suffix(self):
        self.assertEqual(self._f('hot', 'plot'), 3)

    def test_permutation(self):
        self.assertEqual(self._f('ab', 'ba'), 2)

    def test_same(self):
        self.assertEqual(self._f('some', 'some'), 0)

    def test_diff(self):
        self.assertEqual(self._f('some', 'thing'), 9)

    def test_one_empty(self):
        self.assertEqual(self._f('hit', ''), 3)
        self.assertEqual(self._f('', 'hit'), 3)

    def test_both_empty(self):
        self.assertEqual(self._f('', ''), 0)
