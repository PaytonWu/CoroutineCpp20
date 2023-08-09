// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <array>
#include <iostream>

#include <asio.hpp>

asio::awaitable<void> auto_sender(asio::ip::udp::socket & socket, asio::ip::udp::endpoint const & server_endpoint) {
    std::array<char, 1024> data{};
    asio::ip::udp::endpoint sender_endpoint;

    co_await socket.async_connect(server_endpoint, asio::use_awaitable);

    for (auto i = 0; i < 100; ++i)
    {
        std::string str = "Hello, World! " + std::to_string(i);
        std::size_t n = co_await socket.async_send_to(asio::buffer(str), server_endpoint, asio::use_awaitable);
        std::cout << "Sent " << n << " bytes to " << server_endpoint << std::endl;
        n = co_await socket.async_receive_from(asio::buffer(data), sender_endpoint, asio::use_awaitable);
        std::cout << "Received " << n << " bytes from " << sender_endpoint << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
}

int main() {
    try {
        asio::io_context io_context{1};
        asio::signal_set signals{io_context, SIGINT, SIGTERM};
        signals.async_wait([&](auto, auto) { io_context.stop(); });

        asio::ip::udp::socket socket{io_context, {asio::ip::make_address("127.0.0.1"), 54321} };
        socket.non_blocking(true);
        socket.set_option(asio::ip::udp::socket::reuse_address(true));
        // int one = 1;
        // setsockopt(socket.native_handle(), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &one, sizeof(one));
        asio::ip::udp::endpoint server_endpoint{asio::ip::make_address("127.0.0.1"), 12345 };

        asio::co_spawn(io_context, auto_sender(std::ref(socket), std::cref(server_endpoint)), asio::detached);
        io_context.run();
    } catch (std::exception & e) {
        std::cout << "Hello, World!" << std::endl;
    }
    return 0;
}


