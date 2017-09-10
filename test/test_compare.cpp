#include <string>
#include <iostream>
#include <cassert>

#include "../include/string.hpp"

using namespace immutable;

int main() {
    std::string s("abcdefghijklmnopqrstuvwxyz");
    const size_t len = s.size();

    string s1(s);

    assert(s1.substr(0, 8).compare(s1.substr(2, 8)) < 0);
    assert(s1.substr(0, 8).compare(s1.substr(0, 8)) == 0);
    assert(s1.substr(0, 8).compare(s1.substr(0, 9)) < 0);
    assert(s1.substr(0, 8).compare(s1.substr(0, 7)) > 0);

    std::cerr << "[Passed]\n";
    return 0;
}
