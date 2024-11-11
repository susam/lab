#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    for (int i = 0; i < 1000000; i++) {
        std::cout << i << '\n';
    }
}
