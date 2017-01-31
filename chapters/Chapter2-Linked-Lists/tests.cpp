#include "answers.hpp"
#include <gtest/gtest.h>

using namespace ch2;

shared_node create_linked_list(const std::initializer_list<int> &list) {
    if (list.size() == 0)
        return shared_node{};

    shared_node root{};
    for (const auto &num : list) {
        root = std::make_shared<Node>(num, root);
    }

    return root;
}

shared_node node_at(const shared_node linked_list, const std::size_t n) {
    const auto size = get_size(linked_list);

    if (n >= size || not linked_list)
        return shared_node{};

    shared_node curr_node{linked_list};
    for (std::size_t i = 0; i < n; ++i)
        curr_node = curr_node->next;

    return curr_node;
}

void print(const Node &root) {
    const Node *curr = &root;
    while (curr != nullptr) {
        std::cout << curr->value << ", ";
        curr = curr->next.get();
    }
    std::cout << std::endl << std::endl;
}

TEST(Node, Equals) {
    // test with self
    const shared_node node = create_linked_list({1, 2, 3, 4, 5});
    ASSERT_EQ(*node, *node);

    // test with similar node
    const shared_node copy_node = create_linked_list({1, 2, 3, 4, 5});
    ASSERT_EQ(*node, *copy_node);

    // test with different sizes
    const shared_node size_1_node = create_linked_list({42});
    ASSERT_NE(*node, *size_1_node);

    // test with different elements but same size
    const shared_node same_size_node = create_linked_list({5, 4, 3, 2, 1});
    ASSERT_NE(*node, *same_size_node);

    // test with similar node that has more elements
    const shared_node bigger_node = create_linked_list({1, 2, 3, 4, 5, 6, 7,});
    ASSERT_NE(*node, *bigger_node);
}

TEST(Chapter2, Question1) {
    const shared_node null_node{};
    remove_duplicates(null_node);
    ASSERT_FALSE(null_node);

    const auto size1_list = create_linked_list({1});
    auto expected = create_linked_list({1});
    remove_duplicates(size1_list);
    ASSERT_EQ(*expected, *size1_list);

    const auto all_duplicates = create_linked_list({1, 1, 1, 1, 1, 1});
    expected = create_linked_list({1});
    remove_duplicates(all_duplicates);
    ASSERT_EQ(*expected, *all_duplicates);

    const auto no_duplicates = create_linked_list({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    expected = create_linked_list({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    remove_duplicates(no_duplicates);
    ASSERT_EQ(*expected, *no_duplicates);

    const auto some_duplicates = create_linked_list({4, 1, 3, 4, 1, 4});
    expected = create_linked_list({3, 1, 4});
    remove_duplicates(some_duplicates);
    ASSERT_EQ(*expected, *some_duplicates);
}

TEST(Chapter2, Question2) {
    // try null node
    const shared_node null_node{};
    auto result = get_kth_to_last(null_node, 0);
    ASSERT_FALSE(result);

    const auto linked_list = create_linked_list({6, 5, 4, 3, 2, 1});
    const auto size = get_size(linked_list);

    // try with k == list size
    result = get_kth_to_last(linked_list, size);
    ASSERT_FALSE(result);

    // try with k > list size
    result = get_kth_to_last(linked_list, size + 1);
    ASSERT_FALSE(result);

    // try with all valid k values
    for (std::size_t k = 0; k < size; ++k) {
        const auto expected = node_at(linked_list, size - k - 1);
        result = get_kth_to_last(linked_list, k);
        ASSERT_EQ(*expected, *result);
    }
}

// assume list size > 2
TEST(Chapter2, Question3) {
    // try null node
    auto null_node = shared_node{};
    remove_middle(null_node);
    ASSERT_FALSE(null_node);

    // try list with 2 nodes
    auto size_2_list = create_linked_list({2, 1});
    auto expected = create_linked_list({2});
    remove_middle(node_at(size_2_list, 0));
    ASSERT_EQ(*expected, *size_2_list);

    // try list with 3 nodes
    auto size_3_list = create_linked_list({3, 2, 1});
    expected = create_linked_list({3, 1});
    remove_middle(node_at(size_3_list, 1));
    ASSERT_EQ(*expected, *size_3_list);

    // try long list with odd size
    auto odd_long_list = create_linked_list({10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
    expected = create_linked_list({10, 9, 8, 7, 6, 4, 3, 2, 1, 0});
    remove_middle(node_at(odd_long_list, 5));
    ASSERT_EQ(*expected, *odd_long_list);

    // try long list with even size
    auto even_long_list = create_linked_list({9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
    expected = create_linked_list({9, 8, 7, 6, 5, 3, 2, 1, 0});
    remove_middle(node_at(even_long_list, 4));
    ASSERT_EQ(*expected, *even_long_list);
}

TEST(Chapter2, Question4) {
    // try null node
    const auto null_node = shared_node{};
    partition(null_node, 1);
    ASSERT_FALSE(null_node);

    // try list with only elements less than x
    const auto less_than_list = create_linked_list({7, 4, 3, 5, 6, 7});
    auto expected = create_linked_list({7, 4, 3, 5, 6, 7});
    partition(less_than_list, 10);
    ASSERT_EQ(*expected, *less_than_list);

    // try list with only elements greater than x
    const auto greater_than_list = create_linked_list({7, 8, 9, 10, 7, 8, 10});
    expected = create_linked_list({7, 8, 9, 10, 7, 8, 10});
    partition(greater_than_list, 2);
    ASSERT_EQ(*expected, *greater_than_list);

    // try general case where some elements are >= and < x
    const auto general_list = create_linked_list({1, 2, 10, 5, 8, 5, 3});
    expected = create_linked_list({8, 5, 10, 5, 1, 2, 3});
    partition(general_list, 5);
    ASSERT_EQ(*expected, *general_list);
}

TEST(Chapter2, Question5_iterative) {
    // try with null nodes
    const auto null_node = shared_node{};
    auto result = sum(null_node, null_node);
    auto expected = create_linked_list({0});
    ASSERT_EQ( *expected, *result);

    // try with one null node
    auto num1 = shared_node{};
    auto num2 = create_linked_list({4,2});
    result = sum(num1, num2);
    expected = create_linked_list({4,2});
    ASSERT_EQ( *expected, *result);


    // try nums (same length) with no carry afterwords
    num1 = create_linked_list({6,1,7});
    num2 = create_linked_list({2,9,5});
    result = sum(num1, num2);
    expected = create_linked_list({9,1,2});
    ASSERT_EQ( *expected, *result);

    // try nums (same length) with carry afterwards
    num1 = create_linked_list({9,1,2});
    num2 = create_linked_list({2,5,9});
    result = sum(num1, num2);
    expected = create_linked_list({1,1,7,1});
    ASSERT_EQ( *expected, *result);

    // try nums (different length) with no carry afterwords
    num1 = create_linked_list({1,1,2,3});
    num2 = create_linked_list({1,1,1});
    result = sum(num1, num2);
    expected = create_linked_list({1,2,3,4});
    ASSERT_EQ( *expected, *result);
    
    // try nums (different length) with carry afterwords
    num1 = create_linked_list({9,1,2,3});
    num2 = create_linked_list({9,1,1});
    result = sum(num1, num2);
    expected = create_linked_list({1,0,0,3,4});
    ASSERT_EQ( *expected, *result);
}

TEST(Chapter2, Question5_recursive) {
    // try with null nodes
    const auto null_node = shared_node{};
    auto result = recursive_sum(null_node, null_node);
    auto expected = create_linked_list({0});
    ASSERT_EQ( *expected, *result);

    // try with one null node
    auto num1 = shared_node{};
    auto num2 = create_linked_list({4,2});
    result = recursive_sum(num1, num2);
    expected = create_linked_list({4,2});
    ASSERT_EQ( *expected, *result);


    // try nums (same length) with no carry afterwords
    num1 = create_linked_list({6,1,7});
    num2 = create_linked_list({2,9,5});
    result = recursive_sum(num1, num2);
    expected = create_linked_list({9,1,2});
    ASSERT_EQ( *expected, *result);

    // try nums (same length) with carry afterwards
    num1 = create_linked_list({9,1,2});
    num2 = create_linked_list({2,5,9});
    result = recursive_sum(num1, num2);
    expected = create_linked_list({1,1,7,1});
    ASSERT_EQ( *expected, *result);

    // try nums (different length) with no carry afterwords
    num1 = create_linked_list({1,1,2,3});
    num2 = create_linked_list({1,1,1});
    result = recursive_sum(num1, num2);
    expected = create_linked_list({1,2,3,4});
    ASSERT_EQ( *expected, *result);

    // try nums (different length) with carry afterwords
    num1 = create_linked_list({9,1,2,3});
    num2 = create_linked_list({9,1,1});
    result = recursive_sum(num1, num2);
    expected = create_linked_list({1,0,0,3,4});
    ASSERT_EQ( *expected, *result);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}