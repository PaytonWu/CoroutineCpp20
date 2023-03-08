#pragma once

template <typename T>
class [[nodiscard]] simple_task
{
public:
    struct promise_type;
    using coroutine_handle_t = std::coroutine_handle<promise_type>;

private:
    coroutine_handle_t hdl_;

public:
    simple_task(simple_task const &) = delete;
    simple_task &operator=(simple_task const &) = delete;
    simple_task(simple_task &&) = default;
    simple_task &operator=(simple_task &&) = delete;

    simple_task(auto h) : hdl_{h}
    {
        fmt::print("coroutine simple_task<T> constructed\n");
    }

    ~simple_task()
    {
        if (hdl_)
        {
            hdl_.destroy();
        }

        fmt::print("coroutine simple_task<T> destructed\n");
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

template <typename T>
struct simple_task<T>::promise_type
{
    auto get_return_object()
    {
        return simple_task{coroutine_handle_t::from_promise(*this)};
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
