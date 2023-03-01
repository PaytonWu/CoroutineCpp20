#pragma once

#include "corotask.h"

#include <fmt/format.h>

auto process(int index, int total, std::string const &name)
{
    fmt::print("\t{}: process {} of {}\n", name, index, total);
}

coroutine_task coroutine_func(int upper_bound, std::string const &coro_name)
{
    fmt::print("coroutine {} begin\n", coro_name);

    for (auto i = 0; i < upper_bound; ++i)
    {
        process(i, upper_bound, coro_name);
        co_await std::suspend_always{};
        // process(i, upper_bound);
    }

    fmt::print("coroutine {} end\n", coro_name);
}
