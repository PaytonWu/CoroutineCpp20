cmake_minimum_required(VERSION 3.22)

set(CMAKE_TOOLCHAIN_FILE "~/github/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Coroutine CXX)

find_package(fmt CONFIG REQUIRED)
link_libraries(fmt::fmt)

add_compile_options(-fcoroutines)
include_directories(include)

add_subdirectory(example.1)
add_subdirectory(example.2)