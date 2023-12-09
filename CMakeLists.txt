cmake_minimum_required(VERSION 3.0)

project(SnakeGame)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(SnakeGame Main.cpp Source/Game.cpp Source/Food.cpp Source/Snake.cpp )

target_link_libraries(SnakeGame PRIVATE sfml-graphics sfml-window sfml-system)