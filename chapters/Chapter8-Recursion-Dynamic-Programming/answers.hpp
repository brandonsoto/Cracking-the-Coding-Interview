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

    int multiply( const int x, const int y, const int sum ) {
        const auto new_y = y >> 1;
        // TODO: left off here

        // base case
        if ( y <= 0 ) {
            return sum;
        }
        // we can multiply by 2
        else if ( new_y > 0 ) {
            int new_sum = sum;

            if ( new_sum == 0 ) {
                new_sum = x << 1;
            } else {
                new_sum = new_sum << 1;
            }

            return multiply( x, y >> 1, new_sum );
        }
        // we cannot multiply by 2
        else {
            return sum + x;
        }
    }

    // question 6: write a recursive function that multiples 2 positive integers without using the * operator. We can
    // use addition, subtraction, and bit shifting.
    int multiply( const int x, const int y ) {
        if ( x < 0 || y < 0 ) {
            throw std::exception();
        }
        // x is larger number
        // y is smaller number
        const auto larger = x > y ? x : y;
        const auto smaller = x > y ? y : x;
        return multiply( larger, smaller, 0 );
    }



} // end of ch8 namespace
