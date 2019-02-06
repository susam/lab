// Find the minimum number of characters to be deleted in two strings to
// get the same string.

// This solution optimizes the space complexity of the solution in
// DeletionDistanceDP.java by keeping only those memo values that are
// required in each iteration and discarding unneeded memo values.

// Complexity: O(mn) time. O(min(m, n)) space.

class Solution {
    static int deletionDistance(String a, String b) {
        int m = a.length();
        int n = b.length();

        // Ensure n <= m to reduce space complexity.
        if (n > m) {
            int tempLength = m;
            m = n;
            n = tempLength;

            String tempString = a;
            a = b;
            b = tempString;
        }

        int[] prevMemo = new int[n + 1];
        int[] currMemo = new int[n + 1];

        for (int i = 0; i <= m; i++) {
            currMemo = new int[n + 1];
            for (int j = 0; j <= n; j++) {
                if (i == 0)
                    currMemo[j] = j;
                else if (j == 0)
                    currMemo[j] = i;
                else if (a.charAt(i - 1) == b.charAt(j - 1))
                    currMemo[j] = prevMemo[j - 1];
                else
                    currMemo[j] = 1 + Math.min(prevMemo[j], currMemo[j - 1]);
            }

            prevMemo = currMemo;
        }

        return currMemo[n];
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
