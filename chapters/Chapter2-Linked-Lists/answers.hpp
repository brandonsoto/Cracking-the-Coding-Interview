#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <memory>

namespace ch2 {

    struct Node {
        int value;
        std::shared_ptr<Node> next;
        Node() : Node{ 0 } { }
        Node( int val, Node* next = nullptr )
            : value{ val }, next{ next }
        { }
    };

    inline bool operator==( const Node& left, const Node& right ) {
        if ( &left && &right ) {
            return true;
        }

        const Node* curr_left = &left;
        const Node* curr_right = &right;
        while ( curr_left && curr_right ) {
            if ( curr_left->value != curr_right->value ) {
                return false;
            }
            curr_left = curr_left->next.get();
            curr_right = curr_right->next.get();
        }

        return not curr_left && not curr_right;
    }


    /*******************************************************************************************************************
     * 1: Remove Duplicates: Write code to remove duplicates from an unsorted linked list. How would you solve this problem
     * if a temporary buffer is not allowed?
     *
     * - using a singly linked list
     ******************************************************************************************************************/
    void remove_duplicates( Node& root ) {
        Node* curr = &root;

        while ( curr ) {
            Node* runner = curr;
            while ( runner->next ) {
                if ( runner->next->value == curr->value )
                    runner->next = std::move( runner->next->next );
                else
                    runner = runner->next.get();
            }

            curr = curr->next.get();
        }
    }

} // end of ch2 namespace
