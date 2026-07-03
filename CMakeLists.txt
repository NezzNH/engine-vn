cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS off)

project(whatever)

add_executable(yeah main.cpp console.cpp input_handler.cpp)

target_include_directories(yeah PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/headers")