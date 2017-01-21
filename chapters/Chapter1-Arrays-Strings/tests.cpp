#include <gtest/gtest.h>
#include "answers.hpp"

using namespace ch1;

TEST( Chapter1, Question1 ) {
    ASSERT_TRUE( is_unique( "" ) );
    ASSERT_TRUE( is_unique( " " ) );
    ASSERT_TRUE( is_unique( "sa" ) );
    ASSERT_FALSE( is_unique( "sas" ) );
}

TEST( Chapter1, Question2 ) {
    ASSERT_TRUE( is_permutation( "", "" ) );
    ASSERT_FALSE( is_permutation( "", " " ) );
    ASSERT_TRUE( is_permutation( "s", "s" ) );
    ASSERT_TRUE( is_permutation( "sa", "as" ) );
    ASSERT_TRUE( is_permutation( "sassy", "yssas" ) );
    ASSERT_FALSE( is_permutation( "alym", "mylas" ) );
    ASSERT_FALSE( is_permutation( " j", "j" ) );
}

TEST( Chapter1, Question3 ) {
    std::array<char, 14> test1{"hello world"};
    ch1::urlify(test1.data());
    ASSERT_STREQ( test1.data(), "hello%20world" );

    std::array<char, 18> test2{"Mr John Smith"};
    ch1::urlify(test2.data());
    ASSERT_STREQ( test2.data(), "Mr%20John%20Smith" );

    std::array<char, 4> test3{ " " };
    ch1::urlify(test3.data());
    ASSERT_STREQ( test3.data(), "%20" );

    std::array<char, 1> test4{ "" };
    ch1::urlify(test4.data());
    ASSERT_STREQ( test4.data(), "\0" );
}

TEST( Chapter1, Question4 ) {
    ASSERT_FALSE( is_palindrome_permutation( "arraacce" ) );
    ASSERT_FALSE( is_palindrome_permutation( "paul" ) );
    ASSERT_TRUE( is_palindrome_permutation( "racecar" ) );
    ASSERT_TRUE( is_palindrome_permutation( "rraacce" ) );
    ASSERT_TRUE( is_palindrome_permutation( "taco cat" ) );
    ASSERT_TRUE( is_palindrome_permutation( "" ) );
    ASSERT_TRUE( is_palindrome_permutation( " " ) );
}

TEST( Chapter1, Question5 ) {
    ASSERT_TRUE ( is_one_away( "", "" ) );
    ASSERT_TRUE ( is_one_away( " ", " " ) );
    ASSERT_TRUE ( is_one_away( "pale", "ple" ) );
    ASSERT_TRUE ( is_one_away( "pales", "pales" ) );
    ASSERT_TRUE ( is_one_away( "pale", "bale" ) );
    ASSERT_FALSE( is_one_away( "pale", "bake" ) );
    ASSERT_FALSE( is_one_away( "pale", "ohnohh" ) );
    ASSERT_FALSE( is_one_away( "", "pale" ) );
}

TEST( Chapter1, Question6 ) {
    ASSERT_EQ( compress( "" ), "" );
    ASSERT_EQ( compress( " " ), " " );
    ASSERT_EQ( compress( "abcd" ), "abcd" );
    ASSERT_EQ( compress( "aabbcc" ), "aabbcc" );
    ASSERT_EQ( compress( "aabcccccaaa" ), "a2b1c5a3" );
}

int main( int argc, char **argv ) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}