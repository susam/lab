#include <iostream>

int main()
{
    long long n; // 2 <= n <= 200000
    std::cin >> n;

    long long sum = n * (n + 1) / 2;
    for (int i = 0; i < n - 1; i++) {
        int k;
        std::cin >> k;
        sum -= k;
    }

    std::cout << sum << '\n';
}
