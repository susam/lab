// Given a string, find the length of the longest substring without
// repeating characters.

// Complexity: O(n) time. O(min(m, n)) space; m = alphabet size

#include <string>
#include <unordered_map>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        std::unordered_map<char, int> map;

        int n = s.length();
        int max_len = 0;
        int i = 0;
        int j = 0;

        while (j < n) {
            char c = s[j];
            auto it = map.find(c);

            // If c exists in s[i..j], advance i to skip over c.
            if (it != map.end() && it->second >= i) {
                i = it->second + 1;
            }

            map[c] = j;

            int len = j - i + 1;
            if (len > max_len) {
                max_len = len;
            }

            ++j;
        }

        return max_len;
    }
};


// Tests
#include <iostream>

void test(std::string s, int expected)
{
    std::cout << "Input:    " << s << '\n';

    int output = Solution().lengthOfLongestSubstring(s);

    std::cout << "Output:   " << output << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-----\n";

    if (output != expected) {
        std::cout << "TEST FAILURE!\n";
        exit(EXIT_FAILURE);
    }
}

int main()
{
    test("", 0);
    test("a", 1);
    test("abcabcbb", 3);
    test("bbbbb", 1);
    test("pwwkew", 3);
    test("aab", 2);
    test("qrsvbspk", 5);
}
