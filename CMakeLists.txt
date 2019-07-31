cmake_minimum_required(VERSION 3.12)
project(tmln)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O3")

SET(EXECUTABLE_OUTPUT_PATH ../)

add_executable(TextMiningCompiler src/compiler/main.cc src/compiler/trie.cc src/compiler/reader.cc)
add_executable(TextMiningApp src/app/main.cc src/app/file.cc src/app/levenshtein.cc)
