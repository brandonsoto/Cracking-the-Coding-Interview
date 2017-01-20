#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring>

namespace ch1 {

    /*******************************************************************************************************************
     * 1: Is Unique: Implement an algorithm to determine if a string has all unique characters. What if you cannot use
     * data structures?
     * // TODO: should ask if this will be a unicode or ascii string
     ******************************************************************************************************************/
    bool is_unique(const std::string &str) {
        // solution 1: bool array with each index representing a char O(n)
        // * solution 2: no data structs - loop through n characters and compare with the others O(n ^ 2)
        // solution 3: sort and compare adjacent characters O(n log n)
        if (str.empty() || str.size() > 128) // 128 possible characters in ascii
            return true;

        for (std::size_t i = 0; i < str.size() - 1; ++i) {
            const char current_char = str[i];
            for (std::size_t k = i + 1; k < str.size(); ++k) {
                if (current_char == str[k])
                    return false;
            }
        }
        return true;
    }


    /*******************************************************************************************************************
     * 2: Check Permutation: Given 2 strings, write a method to decide if one is a permutation of the other.
     * // TODO: can I modify? What's the char set? Does whitespace matter? Does letter case matter?
     ******************************************************************************************************************/
    bool is_permutation(const std::string &str1, const std::string &str2) {
        // solution 1: sort both strings and compare each char in both O(n log n) - use if I can modify string
        // * solution 2: use a map to count char occurrences O(n)
        // solution 3: linear search and try to find each char in the other string O(n ^ n)

        // assuming whitespace and letter case matter

        if (str1.size() != str2.size())
            return false;

        std::unordered_map<char, int> char_count{};
        for (std::size_t i = 0; i < str1.size(); ++i) {
            ++char_count[str1[i]];
            --char_count[str2[i]];
        }

        for (const auto &pair : char_count) {
            if (pair.second != 0)
                return false;
        }

        return true;
    }

    /*******************************************************************************************************************
     * 3: URLify: Write a method to replace all spaces in a string with '%20'. Assume string has sufficient space at end
     * to hold additional characters, and that you are given the true length of the string. Please use character array.
     * // TODO: ask what is true size? Should it account for other replacement strings?
     ******************************************************************************************************************/
    void urlify(char *const str, const std::size_t size) {
        // solution 1: iterate through each char until space, replace char and move rest - NO
        // solution 2: string stream - works if not in place
        // solution 3: iterate backwards

        constexpr char SEARCH_CHAR = ' '; // the char to be searched for and replaced
        const std::string REPLACEMENT_STRING = "%20"; // replaces search char
        const auto size_difference = REPLACEMENT_STRING.size() - 1;

        // get number of spaces
        std::size_t space_count = 0;
        for ( std::size_t i = 0; i < size; ++i ) {
            if ( str[i] == SEARCH_CHAR )
                ++space_count;
        }

        std::size_t swap_index = size + (space_count * size_difference) - 1;

        str[swap_index--] = '\0';

        for ( std::size_t i = size - size_difference; i >= size_difference; --i ) {
            if ( str[i] == SEARCH_CHAR ) {
                for ( long k = size_difference; k >= 0; --k )
                    str[swap_index--] = REPLACEMENT_STRING[k];
            } else {
                str[swap_index--] = str[i];
            }
        }

    }

    namespace tests {
        // test cases for question 1
        void question1_tests() {
            std::cout << "is unique" << std::endl << std::endl;
            std::vector<std::string> unique_test_cases{"", "s", "sa", "sass"};
            for (const auto &test : unique_test_cases) {
                std::cout << test << " is unique = " << std::boolalpha << ch1::is_unique(test) << std::endl;
            }
        }

        // test cases for question 2
        void question2_tests() {
            std::cout << "-------------------------------------------------------" << std::endl;
            std::cout << "is permutation" << std::endl << std::endl;

            std::vector<std::string> perm_test_cases1{"", "s", "sa", "sassy", "alym", "a ", " h", "hello"};
            std::vector<std::string> perm_test_cases2{"", "s", "as", "yssas", "myla", " a", "j ", "hello "};
            for (std::size_t i = 0; i < perm_test_cases1.size(); ++i) {
                const auto str1 = perm_test_cases1[i];
                const auto str2 = perm_test_cases2[i];
                std::cout << str1 << ", " << str2 << " are perms = " << std::boolalpha
                          << ch1::is_permutation(str1, str2) << std::endl;
            }
        }

        // test cases for question 3
        void question3_tests() {
            std::cout << "-------------------------------------------------------" << std::endl;
            std::cout << "urlify" << std::endl << std::endl;

            std::array<char, 14> test{"hello world"};
            std::array<char, 18> test2{"Mr John Smith"};
            std::array<char, 3> test3{ " " };

            std::cout << strlen(test.data()) << std::endl;

            ch1::urlify(test.data(), strlen(test.data()) + 1);
            std::cout << test.data() << std::endl;

            ch1::urlify(test2.data(), strlen(test2.data()) + 1);
            std::cout << test2.data() << std::endl;
            
            ch1::urlify(test3.data(), strlen(test3.data()) + 1);
            std::cout << test3.data() << std::endl;
        }

    } // end of tests namespace
} // end of ch1 namespace

int main() {
    using namespace ch1::tests;
    question1_tests();
    question2_tests();
    question3_tests();
    return 0;
}