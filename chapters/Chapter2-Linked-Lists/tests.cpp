#include "answers.hpp"
#include <gtest/gtest.h>

using namespace ch2;

shared_node create_linked_list(const std::initializer_list<int> &list) {
    if (list.size() == 0)
        return shared_node{};

    shared_node root{};
    for (const auto &num : list) {
        root = std::make_shared<Node>( num, root );
    }

    return root;
}

shared_node node_at(const shared_node linked_list, const std::size_t n) {
    const auto size = get_size(linked_list);

    if (n >= size || not linked_list)
        return shared_node{};

    shared_node curr_node{linked_list};
    for (std::size_t i = 0; i < n; ++i)
        curr_node = curr_node;

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
    const shared_node node = create_linked_list({1,2,3,4,5});
    ASSERT_EQ( *node, *node );

    // test with similar node
    const shared_node copy_node = create_linked_list({1,2,3,4,5});
    ASSERT_EQ( *node, *copy_node );

    // test with different sizes
    const shared_node size_1_node = create_linked_list({42});
    ASSERT_NE( *node, *size_1_node );

    // test with different elements but same size
    const shared_node same_size_node = create_linked_list({5,4,3,2,1});
    ASSERT_NE( *node, *same_size_node);

    // test with similar node that has more elements
    const shared_node bigger_node = create_linked_list({1,2,3,4,5,6,7,});
    ASSERT_NE( *node, *bigger_node);
}

TEST(Chapter2, Question1) {
    const auto empty_list = create_linked_list({});
    auto expected = create_linked_list({});
    remove_duplicates(empty_list);
    EXPECT_EQ(*expected, *empty_list);

    const auto size1_list = create_linked_list({1});
    expected = create_linked_list({1});
    remove_duplicates(size1_list);
    EXPECT_EQ(*expected, *size1_list);

    const auto all_duplicates = create_linked_list({1, 1, 1, 1, 1, 1});
    expected = create_linked_list({1});
    remove_duplicates(all_duplicates);
    EXPECT_EQ(*expected, *all_duplicates);

    const auto no_duplicates = create_linked_list({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    expected = create_linked_list({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    remove_duplicates(no_duplicates);
    EXPECT_EQ(*expected, *no_duplicates);

    const auto some_duplicates = create_linked_list({4, 1, 3, 4, 1, 4});
    expected = create_linked_list({4, 1, 3});
    remove_duplicates(some_duplicates);
    EXPECT_EQ(*expected, *some_duplicates);
}

TEST(Chapter2, Question2) {
    // try empty list
    const auto empty_list = create_linked_list({});
    auto expected = shared_node{};
    auto result = get_kth_to_last(empty_list, 0);
    EXPECT_EQ(*expected, *result);

    const auto linked_list = create_linked_list({0, 1, 2, 3, 4, 5, 6});
    const auto size = get_size(linked_list);

    // try with k == list size
    expected = shared_node{};
    result = get_kth_to_last(linked_list, size);
    EXPECT_EQ(*expected, *result);

    // try with k > list size
    expected = shared_node{};
    result = get_kth_to_last(linked_list, size + 1);
    EXPECT_EQ(*expected, *result);

    // try with all valid k values
    for (std::size_t k = 0; k < size; ++k) {
        expected = node_at(linked_list, size - k - 1);
        result = get_kth_to_last(linked_list, k);
        EXPECT_EQ(*expected, *result);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}