cmake_minimum_required(VERSION 3.12)
project(Hack_assembler VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

add_library(parser_src src/Parser.cpp)
add_library(code_src src/code.cpp)
add_library(symbol_src src/SymbolTable.cpp)
add_library(assembler_src src/Assembler.cpp)

target_include_directories(parser_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(code_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(symbol_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(assembler_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_link_libraries(assembler_src PRIVATE parser_src code_src symbol_src)



add_executable(main src/main.cpp)
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(main PRIVATE assembler_src)

add_subdirectory(tests)

##testing parser.cpp

##add_executable(assem)
