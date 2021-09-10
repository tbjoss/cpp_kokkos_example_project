#include "config.hpp"
#include "function.hpp"
#include <cstdio>
#include <typeinfo>

int main(int argc, char* argv[]) {
    // You must call initialize() before you may call Kokkos.
    //
    // With no arguments, this initializes the default execution space
    // (and potentially its host execution space) with default
    // parameters.  You may also pass in argc and argv, analogously to
    // MPI_Init().  It reads and removes command-line arguments that
    // start with "--kokkos-".
    Kokkos::initialize(argc, argv);

    // Print the name of Kokkos' default execution space.  We're using
    // typeid here, so the name might get a bit mangled by the linker,
    // but you should still be able to figure out what it is.
    printf("Hello World on Kokkos execution space %s\n",
           typeid(Kokkos::DefaultExecutionSpace).name());

    // Run lambda on the default Kokkos execution space in parallel,
    // with a parallel for loop count of 15.  The lambda's argument is
    // an integer which is the parallel for's loop index.  As you learn
    // about different kinds of parallelism, you will find out that
    // there are other valid argument types as well.
    //
    // For a single level of parallelism, we prefer that you use the
    // KOKKOS_LAMBDA macro.  If CUDA is disabled, this just turns into
    // [=].  That captures variables from the surrounding scope by
    // value.  Do NOT capture them by reference!  If CUDA is enabled,
    // this macro may have a special definition that makes the lambda
    // work correctly with CUDA.  Compare to the KOKKOS_INLINE_FUNCTION
    // macro, which has a special meaning if CUDA is enabled.
    //
    // The following parallel_for would look like this if we were using
    // OpenMP by itself, instead of Kokkos:
    //
    // #pragma omp parallel for
    // for (int i = 0; i < 15; ++i) {
    //   printf ("Hello from i = %i\n", i);
    // }
    //
    // You may notice that the printed numbers do not print out in
    // order.  Parallel for loops may execute in any order.
    // We also need to protect the usage of a lambda against compiling
    // with a backend which doesn't support it (i.e. Cuda 6.5/7.0).
#if defined(KOKKOS_ENABLE_CXX11_DISPATCH_LAMBDA)
    Kokkos::parallel_for(
            20, KOKKOS_LAMBDA(const int i) {
              // printf works in a CUDA parallel kernel; std::ostream does not.
              //printf("Hello from i = %i\n", i);

              ExampleProject::do_something(i);

            });
#endif

    ExampleProject::do_something(100);
    // You must call finalize() after you are done using Kokkos.
    Kokkos::finalize();
}