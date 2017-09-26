#include <memory>
#include <vector>

namespace ch8 {

    using set = std::vector<int>;
    using powerset = std::vector<std::vector<int>>;

    void compute_powerset_recursive( const set& start_set, const std::size_t start_index, powerset& the_powerset ) {
        if ( start_index >= start_set.size() ) {
            return;
        }

        set subset{};

        for ( std::size_t i = start_index; i < start_set.size(); ++i ) {
            subset.emplace_back( start_set[i] );
            the_powerset.push_back( subset );
        }

        compute_powerset_recursive( start_set, start_index + 1, the_powerset );
    }

    void compute_powerset_iterative( const set& start_set, const std::size_t start_index, powerset& the_powerset ) {
        if ( start_index >= start_set.size() ) {
            return;
        }

        for ( std::size_t k = 0; k < start_set.size(); ++k ) {
            set subset{};
            for ( std::size_t i = k; i < start_set.size(); ++i ) {
                subset.emplace_back( start_set[i] );
                the_powerset.push_back( subset );
            }
        }
    }

    // question 5: return the  powerset of a set - iterative solution
    // time = O(n^2)
    powerset compute_powerset_iterative( const set& start_set ) {
        powerset the_powerset{};
        compute_powerset_iterative( start_set, 0, the_powerset );
        return the_powerset;
    }

    // question 5: return the  powerset of a set - recursive solution
    // time = O(n^2)
    powerset compute_powerset_recursive( const set& start_set ) {
        powerset the_powerset{};
        compute_powerset_recursive( start_set, 0, the_powerset );
        return the_powerset;
    }

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



} // end of ch8 namespace
