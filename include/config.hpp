#pragma once

#include "Kokkos_Core.hpp"

namespace ExampleProject {
    static constexpr int SPACE_DIM = 3;

    /// Host:
#define MemSpaceHost Kokkos::HostSpace
#define LayoutHost  Kokkos::LayoutRight

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
#define MemSpace Kokkos::HostSpace
#endif
#ifndef Layout
#define Layout Kokkos::LayoutRight
#endif

    using ExecSpace = MemSpace::execution_space;
    using range_policy = Kokkos::RangePolicy<ExecSpace>;

    using ExecSpaceHost = MemSpaceHost::execution_space;
    using range_policy_host = Kokkos::RangePolicy<ExecSpaceHost>;

    /// my basic vector
    typedef Kokkos::View<double*, Layout , MemSpace> ViewVectorD;
    typedef Kokkos::View<double*[SPACE_DIM], Layout, MemSpace> ViewMatrix3D;

    typedef Kokkos::View<double*, LayoutHost, MemSpaceHost> ViewVectorDHost;
    typedef Kokkos::View<double*[SPACE_DIM], LayoutHost, MemSpaceHost> ViewMatrix3DHost;
}