// Find the minimum number of characters to be deleted in two strings to
// get the same string.

// This is a naive recursive solution.

// Complexity: O(2^n) time. O(n) space.

class DeletionDistanceNaive {
    // Solution
    static int deletionDistance(String a, String b) {
        return deletionDistance(a, b, a.length(), b.length());
    }

    static int deletionDistance(String a, String b, int m, int n) {
        if (m == 0)
            return n;

        if (n == 0)
            return m;

        if (a.charAt(m - 1) == b.charAt(n - 1))
            return deletionDistance(a, b, m - 1, n - 1);

        return 1 + Math.min(deletionDistance(a, b, m - 1, n),
                            deletionDistance(a, b, m, n - 1));
    }

    // Tests
    static void test(String a, String b, int expected) {
        int output = deletionDistance(a, b);
        System.out.printf("Input:    \"%s\", \"%s\"\n", a, b);
        System.out.printf("Output:   %d\n", output);
        System.out.printf("Expected: %d\n", expected);
        System.out.println("-----");

        if (output != expected) {
            System.out.println("TEST FAILURE!");
            System.exit(1);
        }
    }

    public static void main(String[] args) {
        test("heat", "hit", 3);
        test("dog", "frog", 3);
        test("hot", "plot", 3);
        test("ab", "ba", 2);
        test("some", "some", 0);
        test("some", "thing", 9);
        test("hit", "", 3);
        test("", "hit", 3);
        test("", "", 0);
    }
}
