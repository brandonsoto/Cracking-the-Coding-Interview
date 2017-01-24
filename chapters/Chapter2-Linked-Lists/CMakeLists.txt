cmake_minimum_required( VERSION 2.8 )
enable_testing()
add_executable( chapter2 tests.cpp answers.hpp )
target_link_libraries( chapter2 PUBLIC gtest_main )
add_test( NAME chapter2_test COMMAND chapter2 )

