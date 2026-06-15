cmake_minimum_required(VERSION 3.12)
project(Hack_assembler VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_library(parser_src src/Parser.cpp)

target_include_directories(parser_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)




##testing parser.cpp

##add_executable(assem)
