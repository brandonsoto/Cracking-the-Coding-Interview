#include <memory>

namespace ch2 {

    struct Node;

    using shared_node = std::shared_ptr<Node>;

    struct Node {
        int value;
        shared_node next;
        Node() : Node{0, shared_node{}} {}
        Node(const int val, const shared_node& next )
                : value{val}, next{next} {}
    };

    inline bool operator==(const Node &left, const Node &right) {
        if (&left == &right) {
            return true;
        }

        const Node *curr_left = &left;
        const Node *curr_right = &right;
        while (curr_left && curr_right) {
            if (curr_left->value != curr_right->value) {
                return false;
            }
            curr_left = curr_left->next.get();
            curr_right = curr_right->next.get();
        }

        return not curr_left && not curr_right;
    }

    inline bool operator!=( const Node& left, const Node& right ) {
        return not( left == right );
    }


    /*******************************************************************************************************************
     * 1: Remove Duplicates: Write code to remove duplicates from an unsorted linked list. How would you solve this problem
     * if a temporary buffer is not allowed?
     *
     * - using a singly linked list
     ******************************************************************************************************************/
    void remove_duplicates(shared_node root) {
        shared_node curr = root;

        while (curr) {
            shared_node runner = curr;
            while (runner->next) {
                if (runner->next->value == curr->value)
                    runner->next = std::move(runner->next->next);
                else
                    runner = runner->next;
            }

            curr = curr->next;
        }
    }

    std::size_t get_size(const shared_node root) {
        auto curr = root;
        std::size_t size = 0;

        while (curr) {
            ++size;
            curr = curr->next;
        }

        return size;
    }


    /*******************************************************************************************************************
     * 2: Return kth to last: Implement an algorithm to find the kth to last element of a singly linked list.
     * - k = 0 returns the last element
     * - using a singly linked list
     ******************************************************************************************************************/
    shared_node get_kth_to_last(const shared_node root, const std::size_t k) {
        shared_node kth_node{root};
        shared_node runner_node{root};

        // place runner k elements in front
        for (std::size_t i = 0; i <= k; ++i) {
            if (not runner_node)
                return shared_node{};

            runner_node = runner_node->next;
        }

        // move the kth node to the proper location
        while (runner_node) {
            runner_node = runner_node->next;
            kth_node = kth_node->next;
        }

        return kth_node;
    }

    /**
     * 3: Delete Middle Node: Implement an algorithm to delete a node in the middle of a singly linked list,
     * given only access to that node.
     */
    void remove_middle( shared_node middle_node ) {
        if ( not middle_node || not middle_node->next ) { return; }
        middle_node->value = middle_node->next->value;
        middle_node->next = middle_node->next->next;
    }

    /**
     * 4: Partition: Write code to partition a linked list around a value x, such that all nodes less than x come before
     * all nodes greater than or equal to x. If x is contained within the list, the values of x only need to be after
     * the values of x only need to be after the elements less than x. The partition element x can appear anywhere in
     * the "right partition"; it does not need to appear between the left and right partitions.
     */
     void partition( const shared_node root, const int x ) {
        if ( not root ) { return; }

        shared_node partition_node = root;
        shared_node curr_node = root;

        while ( curr_node ) {
            if ( curr_node->value < x ) {
                const auto temp = curr_node->value;
                curr_node->value = partition_node->value;
                partition_node->value = temp;
                partition_node = partition_node->next;
            }

            curr_node = curr_node->next;
        }
    }

    void add_remaining_digits( shared_node num, shared_node result, int& carry ) {
        int sum = 0;
        int remainder = 0;

        while ( num ) {
            sum = num->value  + carry;
            remainder = sum % 10;
            carry = sum >= 10 ? 1 : 0;

            result->value = remainder;

            if ( num->next )
                result->next = std::make_shared<Node>(0, nullptr);

            num = num->next;
            result = result->next;
        }
    }

    /**
     * 5: Sum Lists: You have two numbers represented by a linked list, where each node contains a single
     * digit. The digits are stored in reverse order, such that the 1's digit is at the head of the linked list. Write a
     * function that adds the two numbers and returns the sum as a linked list.
     *
     * Iterative solution
     */
    shared_node sum( shared_node num1, shared_node num2 ) {
        shared_node result = std::make_shared<Node>(0, nullptr);
        shared_node curr_result = result;
        int remainder = 0;
        int carry = 0;
        int sum = 0;

        while ( num1 && num2 ) {
            sum = num1->value + num2->value + carry;
            remainder = sum % 10;
            carry = sum >= 10 ? 1 : 0;

            curr_result->value = remainder;

            if ( num1->next || num2->next ) {
                curr_result->next = std::make_shared<Node>(0, nullptr);
                curr_result = curr_result->next;
            }

            num1 = num1->next;
            num2 = num2->next;
        }

        add_remaining_digits(num1, curr_result, carry);
        add_remaining_digits(num2, curr_result, carry);

        if ( carry > 0 )
            curr_result->next = std::make_shared<Node>(carry, nullptr);

        return result;
    }

    /**
     * 5: Sum Lists: You have two numbers represented by a linked list, where each node contains a single
     * digit. The digits are stored in reverse order, such that the 1's digit is at the head of the linked list. Write a
     * function that adds the two numbers and returns the sum as a linked list.
     *
     * Recursive solution
     */
    shared_node recursive_sum( shared_node num1, shared_node num2, int carry ) {
        const int val1 = num1 ? num1->value : 0;
        const int val2 = num2 ? num2->value : 0;
        const int sum = val1 + val2 + carry;
        const int remainder = sum % 10;
        carry = sum >= 10 ? 1 : 0;
        shared_node result = std::make_shared<Node>( remainder, nullptr );

        // case: both numbers still have digits
        if ( num1 && num2 ) {
            result->next = recursive_sum( num1->next, num2->next, carry );
        }
        // case: num1 still has digits
        else if ( num1 ) {
            result->next = recursive_sum( num1->next, num2, carry );
        }
        // case: num2 still has digits
        else if ( num2 ) {
            result->next = recursive_sum( num1, num2->next, carry );
        }
        // base case: both numbers have no more digits
        else {
            if ( sum > 0 ) {
                return std::make_shared<Node>(sum, nullptr);
            } else {
                return shared_node{};
            }
        }

        return result;
    }

    shared_node recursive_sum( shared_node num1, shared_node num2 ) {
        if ( not num1 && not num2 ) {
            return std::make_shared<Node>(0, nullptr);
        }

        return recursive_sum(num1, num2, 0);
    }


} // end of ch2 namespace
