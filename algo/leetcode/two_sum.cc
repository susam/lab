// Given an array of integers, return indices of the two numbers such
// that they add up to a specific target.
//
// You may assume that each input would have exactly one solution, and
// you may not use the same element twice.

// Complexity: O(n) time. O(n) space.

#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(const std::vector<int>& nums, int target)
    {
        std::unordered_map<int, int> index_map;

        for (int i = 0; i < static_cast<int>(nums.size()); i++) {
            auto value = nums[i];
            auto complement = index_map.find(target - value);

            if (complement == index_map.end()) {
                index_map[value] = i;
            } else {
                return {complement->second, i};
            }
        }
        return {};
    }
};


// Tests
#include <sstream>
#include <string>
#include <iostream>

std::string vector_to_str(const std::vector<int>& v)
{
    std::ostringstream oss;
    oss << '{';
    if (v.size() > 0) {
        oss << v[0];
    }
    for (std::size_t i = 1; i < v.size(); i++) {
        oss << ", " << v[i];
    }
    oss << '}';
    return oss.str();
}

void test(const std::vector<int>& nums, int target,
          const std::vector<int>& expected)
{
    std::cout << "Input:    " << vector_to_str(nums) << ", " << target << '\n';

    auto output = Solution().twoSum(nums, target);

    std::cout << "Output:   " << vector_to_str(output) << '\n';
    std::cout << "Expected: " << vector_to_str(expected) << '\n';
    std::cout << "-----\n";

    if (output != expected) {
        std::cout << "TEST FAILURE!\n";
        exit(EXIT_FAILURE);
    }
}

int main()
{
    test({9}, 9, {});
    test({4, 4}, 8, {0, 1});
    test({5, 4}, 8, {});
    test({4, 4, 1}, 5, {1, 2});
    test({4, 6, 10, 15, 16}, 21, {1, 3});
}
