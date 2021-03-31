#include <iostream>
#include <algorithm>

int main()
{
    std::string s; // 1 <= s.size() <= 1000000
    std::cin >> s;

    int len = 1;
    int max_len = 1;

    for (std::string::size_type i = 1; i < s.size(); i++) {
        if (s[i - 1] == s[i]) {
            ++len;
        } else {
            max_len = std::max(len, max_len);
            len = 1;
        }
    }
    max_len = std::max(len, max_len);
    std::cout << max_len << '\n';
}
