#pragma once

#include <fmt/format.h>

template <typename T>
class [[nodiscard]] tracing_task
{
public:
    struct promise_type;
    using coroutine_handle_t = std::coroutine_handle<promise_type>;

private:
    coroutine_handle_t hdl_;

public:
    tracing_task(tracing_task const &) = delete;
    tracing_task &operator=(tracing_task const &) = delete;
    tracing_task(tracing_task &&) = default;
    tracing_task &operator=(tracing_task &&) = delete;

    tracing_task(auto h) : hdl_{h}
    {
        fmt::print("coroutine tracing_task<T> constructor\n");
    }

    ~tracing_task()
    {
        if (hdl_)
        {
            hdl_.destroy();
        }

        fmt::print("coroutine tracing_task<T> destructor\n");
    }

    bool resume() const
    {
        fmt::print("coroutine tracing_task<T> resume\n");

        if (!hdl_ || hdl_.done())
        {
            return false;
        }

        hdl_.resume();
        return !hdl_.done();
    }
};

template <typename T>
struct tracing_task<T>::promise_type
{
    promise_type()
    {
        fmt::print("coroutine tracing_task<T>::promise_type constructor\n");
    }

    ~promise_type()
    {
        fmt::print("coroutine tracing_task<T>::promise_type destructor\n");
    }

    auto get_return_object()
    {
        fmt::print("coroutine tracing_task<T>::promise_type get_return_object()\n");

        return tracing_task{coroutine_handle_t::from_promise(*this)};
    }

    auto initial_suspend()
    {
        fmt::print("coroutine tracing_task<T>::promise_type initial_suspend()\n");

        return std::suspend_always{};
    }

    void unhandled_exception()
    {
        fmt::print("coroutine tracing_task<T>::promise_type unhandled_exception()\n");
    }

    void return_void()
    {
        fmt::print("coroutine tracing_task<T>::promise_type return_void()\n");
    }

    auto final_suspend() noexcept
    {
        fmt::print("coroutine tracing_task<T>::promise_type final_suspend()\n");

        return std::suspend_always{};
    }
};
