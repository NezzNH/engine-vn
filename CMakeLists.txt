cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS off)

project(whatever)

file(GLOB SOURCES CMAKE_CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(yeah ${SOURCES})

target_include_directories(yeah PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/headers")