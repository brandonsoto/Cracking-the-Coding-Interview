cmake_minimum_required( VERSION 2.8 )
enable_testing()
add_executable( chapter8 tests.cpp answers.hpp )
target_link_libraries( chapter8 PUBLIC gtest_main )
add_test( NAME chapter8_test COMMAND chapter8 )

