#include "corofunc.h"

// #include <gtest/gtest.h>

#include <fmt/format.h>

int main()
{
    fmt::print("example2 begin\n");
    {
        std::string task1_name{"task1"};
        std::string task2_name{"taks2"};

        auto task1 = coroutine_func(3, task1_name);
        auto task2 = coroutine_func(5, task2_name);

        task1.resume();
        fmt::print("task1 suspended\n");

        while (task2.resume())
        {
            fmt::print("task2 suspended\n");
        }

        task1.resume();
        fmt::print("task1 suspended\n");
    }
    fmt::print("example2 end\n");

    return 0;
}
