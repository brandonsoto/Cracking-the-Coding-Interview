#include "answers.hpp"
#include <gtest/gtest.h>
#include <vector>

using namespace ch8;

TEST(Chapter8, Question5) {
    // empty case
    powerset expected{};
    ASSERT_EQ( expected, compute_powerset_recursive( {} ) );
    ASSERT_EQ( expected, compute_powerset_iterative( {} ) );

    // 1 element case
    expected = { { 1 } };
    ASSERT_EQ( expected, compute_powerset_recursive( { 1 } ) );
    ASSERT_EQ( expected, compute_powerset_recursive( { 1 } ) );

    // 3 element case
    expected = { { 1 }, { 1, 2 }, { 1, 2, 3 }, { 2 }, { 2, 3 }, { 3 } };
    ASSERT_EQ( expected, compute_powerset_recursive( { 1, 2, 3 } ) );
    ASSERT_EQ( expected, compute_powerset_iterative( { 1, 2, 3 } ) );
}

// TODO: left off here
TEST(Chapter8, Question6) {
    // zero case
    ASSERT_EQ( 0, multiply( 0, 0 ) );
    ASSERT_EQ( 0, multiply( 5, 0 ) );
    ASSERT_EQ( 0, multiply( 0, 5 ) );

    // multiply by 1
    ASSERT_EQ( 1, multiply( 1, 1 ) );
    ASSERT_EQ( 3, multiply( 3, 1 ) );
    ASSERT_EQ( 3, multiply( 1, 3 ) );

    // multiply by 2
    ASSERT_EQ( 4, multiply( 2, 2 ) );
    ASSERT_EQ( 8, multiply( 4, 2 ) );
    ASSERT_EQ( 8, multiply( 2, 4 ) );

    // multiply N x M
    // odd x odd
    ASSERT_EQ( 45, multiply( 5, 9 ) );
    ASSERT_EQ( 45, multiply( 9, 5 ) );
    // even x even
    ASSERT_EQ( 40, multiply( 5, 8 ) );
    ASSERT_EQ( 40, multiply( 8, 5 ) );
    // N x N (odd)
    ASSERT_EQ( 49, multiply( 7, 7 ) );
    // N x N (even)
    ASSERT_EQ( 64, multiply( 8, 8 ) );
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
