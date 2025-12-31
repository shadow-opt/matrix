cmake_minimum_required(VERSION 3.15)

project(Matrix4HW VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/my_matrix)
add_subdirectory(app)

enable_testing()
add_subdirectory(tests)