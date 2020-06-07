#include <iostream>

int triangular(int n)
{
    return n * (n + 1) / 2;
}

int main()
{
    int result =    3 * triangular(999 /  3)
                 +  5 * triangular(999 /  5)
                 - 15 * triangular(999 / 15);
    std::cout << result << '\n';
}
