from test.test_deletion_distance_naive import DeletionDistanceNaiveTest

from deletion_distance_dp import deletion_distance


class DeletionDistanceDPTest(DeletionDistanceNaiveTest):
    def setUp(self):
        self._f = deletion_distance
