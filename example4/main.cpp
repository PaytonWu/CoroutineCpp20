#include "corofunc.h"

#include <fmt/format.h>

int main()
{
    fmt::print("example4 begin\n");
    {
        std::string task_name{"trace"};
        auto task = coroutine_func3(3, task_name);

        fmt::print("example4 begin loop\n");
        while (task.resume())
        {
            fmt::print("{} suspended\n", task_name);
        }

        fmt::print("example4 end loop\n");
    }
    fmt::print("example4 end\n");

    return 0;
}
