cmake_minimum_required( VERSION 3.5 )
project( Chapter1 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -Wextra" )
add_executable( chapter1 main.cpp )

