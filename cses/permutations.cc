#include <iostream>

int main()
{
    int n; // 1 <= n <= 10^6
    std::cin >> n;

    if (n == 2 || n == 3) {
        std::cout << "NO SOLUTION\n";
        return 0;
    }
    
    for (int k = 2; k <= n; k += 2) {
        std::cout << k << ' ';
    }
    
    for (int k = 1; k <= n; k += 2) {
        std::cout << k << ' ';
    }

    std::cout << '\n';
}
