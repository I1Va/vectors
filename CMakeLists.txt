cmake_minimum_required(VERSION 4.1.1)
project(vectors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(vectors main.cpp)
target_link_libraries(vectors PRIVATE Qt6::Widgets)