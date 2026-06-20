include(FetchContent)

FetchContent_Declare(googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)



add_executable(parser_test parser_test.cpp)
add_executable(code_test code_test.cpp ../src/Parser.cpp)
add_executable(symbol_test symbol_test.cpp ../src/Parser.cpp ../src/code.cpp)

target_link_libraries(parser_test PRIVATE parser_src GTest::gtest_main)

target_link_libraries(code_test PRIVATE code_src GTest::gtest_main)


target_link_libraries(symbol_test PRIVATE symbol_src GTest::gtest_main)


include(GoogleTest)

gtest_discover_tests(parser_test)
gtest_discover_tests(code_test)
gtest_discover_tests(symbol_test)

target_compile_definitions(parser_test PRIVATE TEST_FILES="${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(code_test PRIVATE TEST_FILES="${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(symbol_test PRIVATE TEST_FILES="${CMAKE_CURRENT_SOURCE_DIR}")






