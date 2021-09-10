#pragma once

#include "Kokkos_Core.hpp"

namespace ExampleProject {
    /*
    /// OpenMP:
    typedef Kokkos::OpenMP ExecSpace;
    typedef Kokkos::OpenMP MemSpace;

    typedef Kokkos::LayoutRight  Layout;
    typedef Kokkos::RangePolicy<ExecSpace>  RangePolicy;
     */

    /// Cuda:
    typedef Kokkos::Cuda ExecSpace;
    typedef Kokkos::CudaSpace MemSpace;

    typedef Kokkos::LayoutLeft Layout;
    typedef Kokkos::RangePolicy<ExecSpace>  RangePolicy;
}