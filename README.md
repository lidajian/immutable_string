# Immutable implementation of string

Gain performance advantage over std mutable string when substr is heavily used. (*Over 3.5X faster!*)

**Note: This branch is thread unsafe - when substring of the same string is desctructed in different thread, the reference counter may risk race condition.**

*Thread-safe version is [here](https://github.com/lidajian/immutable_string).*


## For users

### To import

```#include "<DIR>/string.hpp"``` in the top of the .cpp file, use class ```string``` in namespace ```immutable``` and compile with C++11.

### To use in program

```immutable::string``` could be 

* Created from ```const char*``` and ```std::string``` with default new copy

* Random accessed with index

* For-each iterated

* Compared with ```std::string``` and ```immutable::string```

* Created substring from

* Splitted with character into ```std::vector<immutable::string>```

Please refer to the source file for detail.

### To benchmark

In ```benchmark``` directory, run ```./benchmark```

## For developers

### To test

In ```test``` directory, run ```./test```
