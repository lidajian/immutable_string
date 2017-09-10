#include <string>
#include <iostream>
#include <cassert>

#include "../include/string.hpp"

using namespace immutable;

int main() {
    std::string s("abcdefghijklmnopqrstuvwxyz");
    const size_t len = s.size();
    string s1(s);

    assert(s1.compare(s) == 0);

    for (size_t i = 1; i <= len; ++i) {
        for (size_t j = 0; j <= len - i; ++j) {
            const std::string& std_str = s.substr(j, i);
            const string& immutable_str = s1.substr(j, i);
            assert(immutable_str.compare(std_str) == 0);
        }
    }
    std::cerr << "[Passed]\n";

    return 0;
}
