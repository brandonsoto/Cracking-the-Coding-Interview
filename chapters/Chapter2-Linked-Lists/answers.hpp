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

} // end of ch2 namespace
