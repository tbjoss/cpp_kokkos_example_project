#pragma once

#include "config.hpp"

#include <cstdio>

namespace ExampleProject {
    // if you must do manual recsource management follow the rule of 5
    struct S {
        // default constructor
        // does not affect other special member functions
        S() { puts("S()"); }

        // if you define any of the following, you MUST deal with all the others.

        // copy constructor
        S(const S &) { puts ("S(const S &)"); }

        // move constructor
        S(S &&) { puts("S(S &&)"); }

        // copy assignment operator
        S &operator=(const S &) {
            puts("operator=(const S&)");
            return *this;
        }

        // move assignment operator
        S &operator=(S &&) {
            puts("operator=(S &&)");
            return *this;
        }

        // destructor
        ~S() { puts("~S()"); }
    };
}