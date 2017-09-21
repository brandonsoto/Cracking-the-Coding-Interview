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



} // end of ch8 namespace
