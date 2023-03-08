#pragma once

#include "corotask.h"
#include "simple_task.h"

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

simple_task<int> coroutine_func2(int upper_bound, std::string const &coro_name)
{
    fmt::print("coroutine {} begin\n", coro_name);

    for (auto i = 0; i < upper_bound; ++i)
    {
        process(i, upper_bound, coro_name);
        co_await std::suspend_always{};
    }

    fmt::print("coroutine {} end\n", coro_name);
}

coroutine_task coroutine_call_coroutine(int upper_bound, std::string const &coro_name)
{
    fmt::print("coroutine {} begin\n", coro_name);

    std::string const sub_coro_name{"inner_coro"};

    auto sub_task = coroutine_func(upper_bound, sub_coro_name);

    for (auto i = 0; i < upper_bound; ++i)
    {
        process(i, upper_bound, coro_name);
        // sub_task.resume();
        co_await std::suspend_always{};
    }

    fmt::print("coroutine {} end\n", coro_name);
}

coroutine_task coroutine_call_coroutine2(int upper_bound, std::string const &coro_name)
{
    fmt::print("coroutine {} begin\n", coro_name);

#if defined(ENABLE_COMPILE_ERROR)
    std::string const sub_coro_name{"inner_coro"};
    co_await coroutine_func2(upper_bound, sub_coro_name);
#endif

    for (auto i = 0; i < upper_bound; ++i)
    {
        process(i, upper_bound, coro_name);
        co_await std::suspend_always{};
    }

    fmt::print("coroutine {} end\n", coro_name);
}
