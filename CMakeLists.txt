cmake_minimum_required(VERSION 3.16)

project(cpp_search_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(search_engine
    src/main.cpp
    src/document_loader.cpp
    src/tokenizer.cpp
    src/inverted_index.cpp
    src/ranker.cpp
)

target_include_directories(search_engine PRIVATE
    include
)