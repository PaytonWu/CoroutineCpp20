#pragma once

#include <fmt/format.h>

class tracing_awaiter
{
    inline static int cnt{0};
    int id;

public:
    tracing_awaiter(tracing_awaiter const &) = delete;
    tracing_awaiter &operator=(tracing_awaiter const &) = delete;
    tracing_awaiter(tracing_awaiter &&) = default;
    tracing_awaiter &operator=(tracing_awaiter &&) = delete;

    tracing_awaiter() : id{cnt++}
    {
        fmt::print("tracing_awaiter() constructor\n");
    }

    ~tracing_awaiter()
    {
        fmt::print("tracing_awaiter() destructor\n");
    }

    bool await_ready() const noexcept
    {
        fmt::print("tracing_awaiter await_ready()\n");
        return false;
    }

    bool await_suspend(auto) const noexcept
    {
        fmt::print("tracing_awaiter await_suspend()\n");
        return false;
    }

    void await_resume() const noexcept
    {
        fmt::print("tracing_awaiter await_resume\n");
    }
};
