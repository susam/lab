#include <iostream>

std::uint32_t solution1(std::uint32_t max_term)
{
    std::uint32_t sum = 0;
    std::uint32_t prev_term = 1;
    std::uint32_t curr_term = 2;

    while (curr_term <= max_term) {
        if (curr_term % 2 == 0) {
            std::cout << "curr_term: " << curr_term << '\n';
            sum += curr_term;
        }

        std::uint32_t next_term = prev_term + curr_term;
        prev_term = curr_term;
        curr_term = next_term;
    }

    return sum;
}


int main()
{
    std::cout << solution1(4e6) << '\n';
}
