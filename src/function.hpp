#pragma once

#include "Kokkos_Core.hpp"

namespace ExampleProject {

    KOKKOS_INLINE_FUNCTION
    void do_something(int i) {
        //ex.name();
        printf("Hello from do_something i = %i\n", i);
    }

}