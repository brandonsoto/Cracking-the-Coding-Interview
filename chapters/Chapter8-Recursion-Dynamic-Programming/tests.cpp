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
TEST(Chapter8, DISABLED_Question6) {
    // zero case
    ASSERT_EQ( 0, multiply( 0, 0 ) );
    ASSERT_EQ( 0, multiply( 5, 0 ) );
    ASSERT_EQ( 0, multiply( 0, 5 ) );

    // multiply by 1
    ASSERT_EQ( 1, multiply( 1, 1 ) );
    ASSERT_EQ( 3, multiply( 3, 1 ) );
    ASSERT_EQ( 3, multiply( 1, 3 ) );

    std::cout << (1 >> 2) << std::endl;

    // multiply by 2
    ASSERT_EQ( 4, multiply( 2, 2 ) );
    ASSERT_EQ( 8, multiply( 4, 2 ) );
    ASSERT_EQ( 8, multiply( 2, 4 ) );


}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
