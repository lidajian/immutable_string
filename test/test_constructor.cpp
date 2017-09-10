#include <string>
#include <iostream>
#include <cassert>

#include "../include/string.hpp"

using namespace immutable;

int main() {
    std::string s("abcdefghijklmnopqrstuvwxyz");
    const size_t len = s.size();

    string s1(s, 2, 8);
    assert(s1 == s.substr(2, 8));

    string s2(s.data(), len, 2, 8);
    assert(s2 == s.substr(2, 8));

    try {
        string s3(s, 29, 0);
    } catch (std::length_error& e) {
        std::cerr << "[Passed]\n";
        return 0;
    }

    std::cerr << "[Failed]\n";
    return 0;
}
