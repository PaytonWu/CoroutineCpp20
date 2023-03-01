#include "corofunc.h"

// #include <gtest/gtest.h>

#include <string>

int main()
{
    fmt::print("coroutine example begin\n");
    {
        std::string coro_task_name{"coro_task"};
        auto coro_task = coroutine_func(3, coro_task_name);
        fmt::print("coroutine created\n");

        fmt::print("start\n");
        while (coro_task.resume())
        {
            fmt::print("coroutine suspended\n");
        }
        fmt::print("stop\n");
    }
    fmt::print("coroutine example end\n");

    return 0;
}
