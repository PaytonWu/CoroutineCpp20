#include <array>
#include <iostream>

#include <asio.hpp>

asio::awaitable<void> echo(asio::ip::udp::socket & socket) {
    std::cout << "Binding to address " << socket.local_endpoint() << std::endl;

    std::array<char, 1024> data{};
    asio::ip::udp::endpoint sender_endpoint;

    for (;;)
    {
        std::size_t n = co_await socket.async_receive_from(asio::buffer(data), sender_endpoint, asio::use_awaitable);
        std::cout << "Received " << n << " bytes from " << sender_endpoint << std::endl;
        co_await socket.async_send_to(asio::buffer(data, n), sender_endpoint, asio::use_awaitable);
    }
}

int main() {
    try {
        asio::io_context io_context{1};
        asio::signal_set signals{io_context, SIGINT, SIGTERM};
        signals.async_wait([&](auto, auto) { io_context.stop(); });

        asio::ip::udp::socket socket{io_context, {asio::ip::make_address("127.0.0.1"), 12345} };
        socket.non_blocking(true);
        socket.set_option(asio::ip::udp::socket::reuse_address(true));

        asio::co_spawn(io_context, echo(std::ref(socket)), asio::detached);
        io_context.run();
    } catch (std::exception & e) {
        std::cout << "Hello, World!" << std::endl;
    }
    return 0;
}


