cmake_minimum_required( VERSION 3.5 )
project( Chapter1 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -Wextra" )

enable_testing()
find_package( GTest REQUIRED )
add_executable( chapter1 tests.cpp answers.hpp )
target_link_libraries( chapter1 PUBLIC GTest::GTest )
add_test(
        NAME chapter1_test
        COMMAND chapter1 --gtest-color=yes
)

