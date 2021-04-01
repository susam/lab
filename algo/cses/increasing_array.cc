#include <iostream>
#include <algorithm>

int main()
{
    int n; // 1 <= n <= 200000.
    int x; // 1 <= x <= 10^9.
    int max_x = 0;
    long long moves = 0;

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> x;
        max_x = std::max(x, max_x);
        moves += max_x - x;
    }

    std::cout << moves << '\n';
}
