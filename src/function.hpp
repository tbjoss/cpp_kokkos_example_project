#pragma once

#include "config.hpp"

#include "Kokkos_Core.hpp"

#include <cmath>

namespace ExampleProject {
    template<class ViewType> KOKKOS_INLINE_FUNCTION void print(const ViewType &v) {
        printf("[");

        for(size_t n = 0; n < v.extent(0); n++) {
            for(size_t m = 0; m < v.extent(1); m++) {
                if (m != v.extent(1) - 1) {
                    printf("%f,", v(n,m));
                } else {
                    printf("%f\n", v(n,m));
                }
            }
        }
        printf("]\n");
    }

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

        printf("my_function is called on execution space %s\n",
               typeid(ex).name());

        Kokkos::parallel_for(
                Kokkos::RangePolicy<ExecSpace>(ex, 0, data.extent(0)),
        KOKKOS_LAMBDA(int n) {
            do_something(n);
            data(n) *= transform(scale);
        });
    }

    template<class ViewType> KOKKOS_INLINE_FUNCTION constexpr auto
    outer_product(const ViewType &a, const ViewType &b, const int n, const int m) {
        static_assert(ViewType::rank != 0, "Rank must be 0");

        return a(n)*b(m);
        //Kokkos::View<typename ViewType::value_type [SPACE_DIM][SPACE_DIM], Layout, MemSpace> v0;

        //for (size_t n = 0; n < a.extent(0); n++) {
        //    for (size_t m = 0; m < b.extent(0); m++) {
        //        //v[n][m] = a(n) * b(m);
        //        v(n,m) = a(n) * b(m);
        //    }
        //}
    }

    template<class ViewType> KOKKOS_INLINE_FUNCTION constexpr auto inner_product(const ViewType &a, const ViewType &b) {
        static_assert(ViewType::rank != 0, "Rank must be 0");
        assert(a.extent(0) == b.extent(0));

        typename ViewType::value_type s{0.0};

        for (size_t i = 0; i < a.extent(0); i++) {
            s += a(i) * b(i);
        }
        return s;
    }

    template<class ViewType> KOKKOS_INLINE_FUNCTION constexpr auto
    scalar_product(const ViewType &a, const ViewType &b) {
        return std::sqrt(inner_product(a, b));
    }

    template<class ExecSpace, class ViewType>
    void calculate(ExecSpace ex, ViewType data) {
        using namespace Kokkos;
        static_assert(SpaceAccessibility<ExecSpace, typename ViewType::memory_space>::accessible,
                      "Incompatible ViewType and ExecutionSpace");

        printf("calculate is called on execution space %s\n", typeid(ex).name());

        parallel_for(RangePolicy<ExecSpace>(ex, 0, data.extent(0)),
        KOKKOS_LAMBDA(int n) {
            const auto v = subview(data, n, ALL);

            const auto y = scalar_product(v, v);

            const auto v_nm = outer_product(v,v,0,2);

        });
    }
}