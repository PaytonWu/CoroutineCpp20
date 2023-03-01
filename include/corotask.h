#pragma once

#include <fmt/format.h>
#include <coroutine>

class [[nodiscard]] coroutine_task
{
public:
    struct promise_type;
    using coroutine_handle_t = std::coroutine_handle<promise_type>;

private:
    coroutine_handle_t hdl_;

public:
    coroutine_task(coroutine_task const &) = delete;
    coroutine_task &operator=(coroutine_task const &) = delete;
    coroutine_task(coroutine_task &&) = default;
    coroutine_task &operator=(coroutine_task &&) = delete;

    coroutine_task(auto h) : hdl_{h}
    {
        fmt::print("coroutine task constructed\n");
    }

    ~coroutine_task()
    {
        if (hdl_)
        {
            hdl_.destroy();
        }

        fmt::print("coroutine task destructed\n");
    }

    bool resume() const
    {
        if (!hdl_ || hdl_.done())
        {
            return false;
        }

        hdl_.resume();
        return !hdl_.done();
    }
};

struct coroutine_task::promise_type
{
    auto get_return_object()
    {
        return coroutine_task{coroutine_handle_t::from_promise(*this)};
    }

    auto initial_suspend()
    {
        return std::suspend_always{};
    }

    void unhandled_exception()
    {
    }

    void return_void()
    {
    }

    auto final_suspend() noexcept
    {
        return std::suspend_always{};
    }
};
