cmake_minimum_required(VERSION 3.14)
project(n-body-prac VERSION 1.0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(Matplot++ REQUIRED)
add_executable(n-body main.cpp)
target_link_libraries(n-body PUBLIC Matplot++::matplot)

