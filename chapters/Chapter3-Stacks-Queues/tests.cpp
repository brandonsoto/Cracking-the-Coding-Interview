#include "answers.h"
#include <gtest/gtest.h>

using namespace ch3;

TEST( Chapter3, Question2 ) {
    Stack stack;

//     try empty stack
//    ASSERT_THROW( stack.min(), std::exception() );

    // try min is all elements
    stack.clear();
    stack.push( 0 ).push( 0 ).push( 0 ).push( 0 ).push( 0 );
    ASSERT_EQ( 0, stack.min() );

    // try min in middle
    stack.push( 5 ).push( -10 ).push( 2 ).push( 0 ).push( 10 );
    ASSERT_EQ( -10, stack.min() );

    // try min is top
    stack.push( 8 ).push( 7 ).push( 6 ).push( 2 ).push( 5 ).push( -10 );
    ASSERT_EQ( -10, stack.min() );

    // try min is bottom
    stack.push( -10 ).push( 10 ).push( 2 ).push( 0 ).push( 10 );
    ASSERT_EQ( -10, stack.min() );
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

