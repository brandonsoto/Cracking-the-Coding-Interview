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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
