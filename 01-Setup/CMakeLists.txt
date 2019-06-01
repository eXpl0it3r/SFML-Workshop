cmake_minimum_required(VERSION 3.1)

project(01-Setup)

set (CMAKE_CXX_STANDARD 17)

find_package(SFML 2 COMPONENTS graphics REQUIRED)
add_executable(01-Setup src/main.cpp)
target_link_libraries(01-Setup sfml-graphics)