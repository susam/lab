import unittest
from DeletionDistanceDP import deletion_distance
from test.testDeletionDistanceNaive import DeletionDistanceNaiveTest


class DeletionDistanceDPTest(DeletionDistanceNaiveTest):
    def setUp(self):
        self._f = deletion_distance
