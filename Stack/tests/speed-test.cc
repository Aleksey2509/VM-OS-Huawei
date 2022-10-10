#include "Stack.hh"
#include <chrono>
#include <iostream>

static constexpr size_t ACTION_AMOUNT = 1e6;
static constexpr long long TIMEOUT_MILLISECONDS = 1000;

static const char SET_FAIL_COLOR[] = "\033[0;31m";
static const char SET_PASS_COLOR[] = "\033[0;32m";
static const char SET_DEFAULT_COLOR[] = "\033[0m";


int main()
{
    custom_containers::Stack<size_t> test{};

    std::cout << " Starting speed test " << std::endl;


    auto start = std::chrono::high_resolution_clock::now();
    for (size_t num = 0; num < ACTION_AMOUNT; ++num)
    {
        test.Push(num);
        test.Pop();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << " Ended speed test" << std::endl;
    if (duration.count() < TIMEOUT_MILLISECONDS)
    {
        std::cout << SET_PASS_COLOR << " Speed test passed: duration: " << duration.count() << SET_DEFAULT_COLOR << std::endl;
        return 0;
    }

    std::cout << SET_FAIL_COLOR << " Speed test failed! : duration: " << duration.count() << SET_DEFAULT_COLOR << std::endl;
    return 1;

}