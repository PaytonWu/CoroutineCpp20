#include "corofunc.h"

#include <fmt/format.h>

int main()
{
    fmt::print("example3 begin\n");
    {
        std::string task_name{"task1"};
        auto task = coroutine_call_coroutine(3, task_name);

        while (task.resume())
        {
            fmt::print("{} suspended\n", task_name);
        }

        fmt::print("{} suspended\n", task_name);
    }
    fmt::print("example3 end\n");

    return 0;
}
