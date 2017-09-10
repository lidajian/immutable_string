#include <string>
#include <chrono>
#include <iostream>
#include <cstring>

#include "../include/string.hpp"

using namespace std;

#define LOOPS 100
#define LENGTH 1000

int main() {
    using chrono::system_clock;
    char arr[LENGTH];
    memset(arr, 'a', LENGTH);
    const size_t l = LENGTH;
    string s(arr, l);
    immutable::string ims(arr, l);

    system_clock::time_point t1 = system_clock::now();
    for (int loop = 0; loop < LOOPS; loop++)
    for (int i = 1; i <= l; i++) {
        for (int j = 0; j <= l - i; j++) {
            const string& temp = s.substr(j, i);
        }
    }

    system_clock::time_point t2 = system_clock::now();
    for (int loop = 0; loop < LOOPS; loop++)
    for (int i = 1; i <= l; i++) {
        for (int j = 0; j <= l - i; j++) {
            const immutable::string& temp = ims.substr(j, i);
        }
    }
    system_clock::time_point t3 = system_clock::now();

    cerr << "[Result]\n";
    cerr << "std string: " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << "ms"<< endl;
    cerr << "immutable string: " << chrono::duration_cast<chrono::milliseconds>(t3 - t2).count() << "ms" << endl;

    return 0;
}
