cmake_minimum_required(VERSION 3.20)

project(riscy_emu VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(riscy_emu src/main.cpp)
