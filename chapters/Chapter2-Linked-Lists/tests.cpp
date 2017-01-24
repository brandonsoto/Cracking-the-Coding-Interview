#include <gtest/gtest.h>
#include "answers.hpp"

using namespace ch2;

std::unique_ptr<Node> create_list(const std::initializer_list<int> &list) {
    if (list.size() == 0)
        return std::unique_ptr<Node>(nullptr);

    Node *root = nullptr;
    for (const auto &num : list) {
        root = new Node{num, root};
    }

    return std::unique_ptr<Node>(root);
}

void print(const Node &root) {
    const Node *curr = &root;
    while (curr != nullptr) {
        std::cout << curr->value << std::endl;
        curr = curr->next.get();
    }
    std::cout << std::endl << std::endl;
}

TEST(Chapter2, Question1) {
    auto empty_list = create_list({});
    auto expected = create_list({});
    remove_duplicates(*empty_list.get());
    EXPECT_EQ(*expected, *empty_list);

    auto size1_list = create_list({1});
    expected = create_list({1});
    remove_duplicates(*size1_list.get());
    EXPECT_EQ(*expected, *size1_list);

    auto all_duplicates = create_list({1, 1, 1, 1, 1, 1});
    expected = create_list({1});
    remove_duplicates(*all_duplicates.get());
    EXPECT_EQ(*expected, *all_duplicates);

    auto no_duplicates = create_list({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    expected = create_list({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    remove_duplicates(*no_duplicates.get());
    EXPECT_EQ(*expected, *no_duplicates);

    auto some_duplicates = create_list({4,1,3,4,1,4});
    expected = create_list({4,1,3});
    remove_duplicates(*some_duplicates.get());
    EXPECT_EQ(*expected, *some_duplicates);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}