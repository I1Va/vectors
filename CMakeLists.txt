cmake_minimum_required(VERSION 3.16)

project(Vectors LANGUAGES CXX)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

add_executable(Vectors main.cpp src/geometry.cpp src/visual.cpp)

target_include_directories(Vectors
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(Vectors PRIVATE SFML::Graphics SFML::Audio SFML::Network)

