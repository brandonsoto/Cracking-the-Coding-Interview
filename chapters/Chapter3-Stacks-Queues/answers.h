#include <memory>
#include <limits>

namespace ch3 {
    class Node {
    public:
        int data_;
        int minimum_;
        std::shared_ptr<Node> next_;
        explicit Node( int data ) : data_{ data }, next_{ nullptr } { }

    };

    // LIFO - last in, first out
    // useful for recursive algorithms
    //     - push temp data onto stack as you recurse, remove them as you backtrack
    //     - used to implement recursive algorithm iteratively
    class Stack {
    private:
        std::shared_ptr<Node> top_node_{};
        int minimum_{ std::numeric_limits<int>::max() };
    public:
        explicit Stack( const int value ) {
            push( value );
        }

        Stack() = default;

        int pop() {
            if ( not top_node_ ) { throw std::exception(); }
            const int item = top_node_->data_;
            top_node_ = top_node_->next_;
            return item;
        }

        void clear() {
            top_node_ = nullptr;
            minimum_ = std::numeric_limits<int>::max();
        }

        Stack& push( const int item ) {
            std::shared_ptr<Node> next = std::make_shared<Node>( item );
            next->next_ = top_node_;
            if ( top_node_ ) {
                next->minimum_ = ( next->data_ < top_node_->minimum_ ) ? next->data_ : top_node_->minimum_;
            } else {
                next->minimum_ = next->data_;
            }
            top_node_ = next;
            return *this;
        }

        int peek() const {
            if ( not top_node_ ) { throw std::exception(); }
            return top_node_->data_;
        }

        bool is_empty() const {
            return not top_node_;
        }

        /*******************************************************************************************************************
         * 2: Stack Min: How would you design a stack which, in addition to push and pop, has a function min which
         * returns the minimum element? Push, pop, min should all operate in O(1) time.
         ******************************************************************************************************************/
        int min() const {
            if ( is_empty() ) { throw std::exception{}; }
            return top_node_->minimum_;
        }
    };

    // FIFO - first in, first out
    // often used in breadth-first search or in implementing a cache
    //   - each time we process a node, we add its adjacent nodes to the back of the queue
    class Queue {
    private:
        std::shared_ptr<Node> first_;
        std::shared_ptr<Node> last_;

    public:
        void add( const int item ) {
            std::shared_ptr<Node> next = std::make_shared<Node>( item );
            if ( last_ ) {
                last_->next_ = next;
            }

            last_ = next;

            if ( not first_ ) {
                first_ = last_;
            }
        }

        int remove() {
            if ( not first_ ) {
                throw std::exception{};
            }

            const int data = first_->data_;

            first_ = first_->next_;

            if ( not first_ ) {
                last_ = nullptr;
            }

            return data;
        }

        int peek() const {
            if ( not first_ ) {
                throw std::exception{};
            }

            return first_->data_;
        }

        bool is_empty() const {
            return not first_;
        }
    };



} // end of ch3 namespace
