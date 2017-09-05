#include <memory>
#include <limits>
#include <vector>

namespace ch3 {
    class Node {
    public:
        int data_;
        int minimum_{ std::numeric_limits<int>::max() };
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
        std::size_t size_{ 0 };
    public:
        explicit Stack( const int value ) {
            push( value );
        }

        Stack() = default;

        int pop() {
            if ( not top_node_ ) { throw std::exception(); }
            const int item = top_node_->data_;
            top_node_ = top_node_->next_;
            --size_;
            return item;
        }

        void clear() {
            top_node_ = nullptr;
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
            ++size_;
            return *this;
        }

        int peek() const {
            if ( not top_node_ ) { throw std::exception(); }
            return top_node_->data_;
        }

        bool is_empty() const { return not top_node_; }

        std::size_t size() const { return size_; }

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

    class Set_of_Stacks {
    private:
        std::vector<Stack> stacks_{};
        static const std::size_t MAX_STACK_SIZE{ 5 };
    public:
        Set_of_Stacks() = default;

        void push( const int value ) {
            const auto index = stacks_.size() - 1;

            if ( stacks_.empty() || stacks_[index].size() == MAX_STACK_SIZE ) { // stack set is empty or stack is full
                stacks_.emplace_back( value );
            } else {
                stacks_[index].push( value ); // push to existing stack
            }
        }

        int pop() {
            return pop_at( stacks_.size() - 1 );
        }

        int pop_at( const std::size_t index ) {
            const bool index_valid = /* index >= 0 && */ index < stacks_.size(); // >= 0 is always true because unsigned

            if ( not index_valid ) {
                throw std::exception{};
            }

            const auto value = stacks_[index].pop();

            if ( stacks_[index].is_empty() ) { // no more elements in stack
                stacks_.erase( stacks_.begin() + index );
            }

            return value;
        }

    };



} // end of ch3 namespace
