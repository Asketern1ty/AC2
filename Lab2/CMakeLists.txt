cmake_minimum_required(VERSION 3.16)
project(calculator_make_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(calc STATIC
    src/calc.cpp
)

target_include_directories(calc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(calculator
    src/main.cpp
)

target_link_libraries(calculator PRIVATE calc)
