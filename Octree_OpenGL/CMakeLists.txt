project("Curso de Dimensionalidad")

cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories($(CMAKE_CURRENT_SOURCE_DIR)/source)

add_executable(course_dimensionality source/main.cpp)