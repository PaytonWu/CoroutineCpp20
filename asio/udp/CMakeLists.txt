cmake_minimum_required(VERSION 3.26)
project(test_asio)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -DNOMINMAX -D_WIN32_WINNT=0x0600 -DWIN32_LEAN_AND_MEAN)
endif ()

add_executable(server server/server.cpp)
target_link_libraries(server PRIVATE ws2_32)

add_executable(client client/client.cpp)
target_link_libraries(client PRIVATE ws2_32)
