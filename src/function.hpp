#pragma once

#include "config.hpp"

#include "Kokkos_Core.hpp"

namespace ExampleProject {

    KOKKOS_INLINE_FUNCTION
    void do_something(int i) {
        printf("Hello from do_something i = %i\n", i);
    }

    KOKKOS_INLINE_FUNCTION
    double transform(const double d) {
        return d * d;
    }

    template<class ExecSpace, class ViewType>
    void my_function(ExecSpace ex, ViewType data, double scale) {
        static_assert(Kokkos::SpaceAccessibility<ExecSpace, typename ViewType::memory_space>::accessible,
                      "Incompatible ViewType and ExecutionSpace");

        Kokkos::parallel_for(
                Kokkos::RangePolicy<ExecSpace>(ex, 0, data.extent(0)),
        KOKKOS_LAMBDA(int n) {
            do_something(n);
            data(n) *= transform(scale);
        });
    }
}