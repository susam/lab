// Find the minimum number of characters to be deleted in two strings to
// get the same string.

// This solution optimizes the recursive solution in
// DeletionDistanceNaive.java using dynamic programming.

// Complexity: O(mn) time. O(mn) space.

class Solution {
    static int deletionDistance(String a, String b) {
        int m = a.length();
        int n = b.length();

        int[][] memo = new int[m + 1][n + 1];

        for (int i = 0; i <= m; i++)
            for (int j = 0; j <= n; j++)
                if (i == 0)
                    memo[i][j] = j;
                else if (j == 0)
                    memo[i][j] = i;
                else if (a.charAt(i - 1) == b.charAt(j - 1))
                    memo[i][j] = memo[i - 1][j - 1];
                else
                    memo[i][j] = 1 + Math.min(memo[i - 1][j], memo[i][j - 1]);

        return memo[m][n];
    }
}

class Test {
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

    private static void test(String a, String b, int expected) {
        System.out.printf("Input:    \"%s\", \"%s\"\n", a, b);

        int output = Solution.deletionDistance(a, b);

        System.out.printf("Output:   %d\n", output);
        System.out.printf("Expected: %d\n", expected);
        System.out.println("-----");

        if (output != expected) {
            System.out.println("TEST FAILURE!");
            System.exit(1);
        }
    }
}
