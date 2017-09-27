#include <memory>
#include <vector>
#include <iostream>

namespace ch8 {

    int multiply_helper( const int larger, const int smaller ) {
        // base cases - 0 and 1
        if ( smaller <= 0 ) {
            return 0;
        } else if ( smaller == 1 ) {
            return larger;
        }

        const auto half_product = multiply_helper( larger, smaller >> 1 );

        // smaller is even
        if ( smaller % 2 == 0 ) {
            return half_product + half_product;
        }
        // smaller is odd
        else {
            return half_product + half_product + larger;
        }
    }

    // question 6: write a recursive function that multiples 2 positive integers without using the * operator. We can
    // use addition, subtraction, and bit shifting.
    int multiply( const int x, const int y ) {
        if ( x < 0 || y < 0 ) {
            throw std::exception();
        }

        const auto larger = x > y ? x : y;
        const auto smaller = x > y ? y : x;
        return multiply_helper( larger, smaller );
    }


    std::vector<std::string> compute_permutation( const std::string& string ) {
        std::vector<std::string> perms{};

        if ( string.empty() ) { // base case - empty string
            perms.emplace_back("");
            return perms;
        }

        const std::string first{ string.at( 0 ) };
        const auto remainder = string.substr( 1 );

        // recursive case - get permutations of str[1:]
        const auto words = compute_permutation( remainder );

        // add first to all positions in word
        for ( const auto& word : words ) {
            for ( std::size_t i = 0; i <= word.size(); ++i ) {
                auto str = word;
                str.insert( i, first );
                perms.push_back( str );
            }
        }

        return perms;
    }

} // end of ch8 namespace
