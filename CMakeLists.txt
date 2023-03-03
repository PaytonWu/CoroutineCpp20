cmake_minimum_required(VERSION 3.22)

if (NOT DEFINED ENV{VCPKG_HOME})
    message(FATAL_ERROR "VCPKG_HOME enviornment variable not defined")
endif()

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_HOME}/scripts/buildsystems/vcpkg.cmake")

project(CoroutineCpp20Example CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt CONFIG REQUIRED)
link_libraries(fmt::fmt)

# enable_testing()
# find_package(GTest CONFIG REQUIRED)
# include(GoogleTest)
# link_libraries(GTest::gtest GTest::gtest_main)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fcoroutines)
endif()

include_directories(include)

add_subdirectory(example1)
add_subdirectory(example2)
add_subdirectory(example3)
