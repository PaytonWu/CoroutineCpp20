#include "corofunc.h"

// #include <gtest/gtest.h>

#include <fmt/format.h>

int main()
{
    fmt::print("example3 begin\n");
    {
        std::string task_name{"task1"};
        // std::string task2_name{"taks2"};

        auto task = coroutine_func2(3, task_name);
        // auto task2 = coroutine_func(5, task2_name);

        // task1.resume();
        // fmt::print("task1 suspended\n");

        while (task.resume())
        {
            fmt::print("task2 suspended\n");
        }

        // task1.resume();
        fmt::print("task1 suspended\n");
    }
    fmt::print("example3 end\n");

    return 0;
}
