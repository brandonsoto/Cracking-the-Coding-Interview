cmake_minimum_required( VERSION 2.8 )
enable_testing()
add_executable( chapter1 tests.cpp answers.hpp )
target_link_libraries( chapter1 PUBLIC gtest_main )
add_test( NAME chapter1_test COMMAND chapter1 )

