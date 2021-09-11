#pragma once

#include "Kokkos_Core.hpp"

namespace ExampleProject {

    /// OpenMP:
#ifdef KOKKOS_ENABLE_OPENMP
#define  MemSpace Kokkos::OpenMP
#define Layout Kokkos::LayoutRight
#endif

    /// Cuda:
#ifdef KOKKOS_ENABLE_CUDA
#define MemSpace Kokkos::CudaSpace
#define Layout Kokkos::LayoutLeft
#endif

    // if we do not have a specific memory space we use the host space
#ifndef MemSpace
#define MemSpace Kokkos::Kokkos::HostSpace
#endif
#ifndef Layout
#define Layout Kokkos::LayoutRight
#endif

    using ExecSpace = MemSpace::execution_space;
    using range_policy = Kokkos::RangePolicy<ExecSpace>;

    /// my basic vector
    typedef Kokkos::View<double*, Layout , MemSpace> ViewVectorD;
}