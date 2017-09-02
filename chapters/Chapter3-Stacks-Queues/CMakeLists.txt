cmake_minimum_required( VERSION 2.8 )
enable_testing()
add_executable( chapter3 tests.cpp answers.h )
target_link_libraries( chapter3 PUBLIC gtest_main )
add_test( NAME chapter3_test COMMAND chapter3 )

