#include <iostream>

int main()
{
    long long n; // 1 <= n <= 10^6
    std::cin >> n;
    while (n != 1) {
        std::cout << n << ' ';
        n = (n % 2 == 0) ? (n / 2) : (3 * n + 1);
    }
    std::cout << n << '\n';
}
