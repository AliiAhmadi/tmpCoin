cmake_minimum_required(VERSION 3.10)

project(tmpCoin VERSION 1.0)
find_package(PkgConfig REQUIRED)
pkg_check_modules(UUID REQUIRED uuid)

set(CMAKE_CXX_COMPILER "g++-13")
set(CMAKE_C_COMPILER "cc")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(tmpCoin src/main.cpp)
target_link_libraries(tmpCoin PRIVATE uuid)