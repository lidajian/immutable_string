/*
 * Implementation of immutable string
 */

#ifndef IMMUTABLE_STRING_H
#define IMMUTABLE_STRING_H

#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <memory>

namespace immutable {

    class string {

        public:
            typedef const char* iterator;

            // Default
            string() noexcept:
            _data(NULL),
            _ref(NULL),
            _begin(NULL),
            _end(NULL),
            _len(0)                                                 {}

            // From char array
            string(const char* data,
                    size_t data_len,
                    size_t offset = 0,
                    size_t len = std::string::npos,
                    bool copy = true):
            _data(NULL),
            _ref(NULL),
            _begin(NULL),
            _end(NULL),
            _len(0)                                                 {
                init(data, data_len, offset, len, copy);
            }

            // From std::string
            string(const std::string& str,
                    size_t offset = 0,
                    size_t len = std::string::npos,
                    bool copy = true): // hold by default in case str.data() changes
            _data(NULL),
            _ref(NULL),
            _begin(NULL),
            _end(NULL),
            _len(0)                                                 {
                size_t data_len = str.size();
                const char* data = str.data();
                init(data, data_len, offset, len, copy);
            }

            // From string
            string(const string& str,
                    size_t offset = 0,
                    size_t len = std::string::npos,
                    bool copy = false):
            _data(NULL),
            _ref(NULL),
            _begin(NULL),
            _end(NULL),
            _len(0)                                                 {
                const size_t& data_len = str._len;
                const char* const& data = str._begin;
                init(data, data_len, offset, len, copy);
                if (str._data) {
                    _data = str._data;
                    _ref = str._ref;
                    ++(*_ref);
                }
            }

            // Destructor
            ~string()                                               {
                if (_data) {
                    if (--(*_ref) == 0) {
                        delete _ref;
                        delete[] _data;
                    }
                }
            }

            // Get length of the string
            inline size_t size() const noexcept                     {
                return _len;
            }

            // Get length of the string
            inline size_t length() const noexcept                   {
                return _len;
            }

            // Get begin iterator
            inline iterator begin() const noexcept                  {
                return _begin;
            }

            // Get end iterator
            inline iterator end() const noexcept                    {
                return _end;
            }

            // Access the string at pos
            inline const char& at(size_t pos) const                 {
                if (pos >= _len) {
                    throw std::out_of_range("Access position out of range");
                }
                return _begin[pos];
            }

            // Access the string at pos
            const char& operator[] (size_t pos) const               {
                return at(pos);
            }

            // Create substring of length len from offset
            string substr(size_t offset = 0,
                    size_t len = std::string::npos)                 {
                return string(*this, offset, len);
            }

            // Split with delimiter character
            std::vector<string> split(const char& delimiter)        {
                std::vector<string> tokens;
                if (_begin == NULL) {
                    return tokens;
                }
                size_t __start = 0;
                for (size_t i = 0; i <= _len; ++i) {
                    if (i == _len || _begin[i] == delimiter) {
                        tokens.emplace_back(*this, __start, i - __start);
                        __start = i + 1;
                    }
                }
                return tokens;
            }

            bool operator== (const string& str) const noexcept      {
                if (_len != str._len) {
                    return false;
                } else if (_begin == str._begin) {
                    return true;
                } else {
                    iterator it1 = _begin;
                    iterator it2 = str._begin;
                    while (it1 < _end) {
                        if (*it1 != *it2) {
                            return false;
                        }
                        ++it1;
                        ++it2;
                    }
                    return true;
                }
            }

            bool operator== (const std::string& str) const noexcept {
                return compare(str) == 0;
            }

            // Compared to string
            int compare(const string& str) const noexcept           {
                if (_begin == str._begin && _len == str._len) {
                    return 0;
                } else {
                    iterator it1 = _begin;
                    iterator it2 = str._begin;
                    while (it1 < _end && it2 < str._end) {
                        if (*it1 < *it2) {
                            return -1;
                        } else if (*it1 > *it2) {
                            return 1;
                        }
                        ++it1;
                        ++it2;
                    }
                    if (_len == str._len) {
                        return 0;
                    }
                    return _len > str._len ? 1 : -1;
                }
            }

            // Compared to std::string
            int compare(const std::string& str) const noexcept      {
                iterator it = _begin;
                for (const char& c: str) {
                    if (it == _end) {
                        break;
                    } else if (*it < c) {
                        return -1;
                    } else if (*it > c) {
                        return 1;
                    }
                    ++it;
                }
                if (_len == str.size()) {
                    return 0;
                }
                return _len > str.size() ? 1 : -1;
            }

            friend std::ostream& operator<< (std::ostream& os, const string& str);

        protected:

            template<typename T>
                inline const T& min(const T& v1, const T& v2)       {
                    return v1 < v2 ? v1 : v2;
                }

            void init(const char* const& data,
                    const size_t& data_len,
                    const size_t& offset,
                    const size_t& len,
                    const bool& copy)                               {
                if (offset > data_len) {
                    throw std::length_error("The offset is greater than length");
                }
                _len = min(len, data_len - offset);
                if (copy) {
                    char* __data = new char[_len]; // std::bad_alloc
                    strncpy(__data, data + offset, _len);
                    _data = __data;
                    _ref = new int(1);
                    _begin = __data;
                } else {
                    _begin = data + offset;
                }
                _end = _begin + _len;
            }

        private:
            // Data pointer
            const char * _data;

            // Reference count
            int* _ref;

            // Begin pointer
            iterator _begin;

            // End pointer
            iterator _end;

            // Length of the string
            size_t _len;
    };

    std::ostream& operator<< (std::ostream& os, const string& str)  {
        if (str._begin != NULL) {
            os.write(str._begin, str._len);
        }
        return os;
    }

}

#endif
