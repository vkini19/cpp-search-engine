cmake_minimum_required(VERSION 3.16)

project(cpp_search_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(search_engine
    src/main.cpp
)

target_include_directories(search_engine PRIVATE
    include
)