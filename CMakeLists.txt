cmake_minimum_required(VERSION 3.12)
project(tmln)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O3")

add_executable(compiler src/compiler/main.cc src/compiler/trie.cc src/compiler/reader.cc)
