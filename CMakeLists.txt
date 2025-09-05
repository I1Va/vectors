cmake_minimum_required(VERSION 4.1.1)
project(vectors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)


add_executable(vectors main.cpp src/geometry.cpp src/visual.cpp)

target_include_directories(vectors
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
)


set_target_properties(vectors PROPERTIES AUTOMOC ON)

target_link_libraries(vectors PRIVATE Qt6::Widgets)