#include "config.hpp"
#include "function.hpp"
#include "struct.hpp"

#include <cstdio>
#include <typeinfo>

int main(int argc, char* argv[]) {
    using namespace ExampleProject;
    // You must call initialize() before you may call Kokkos.
    //
    // With no arguments, this initializes the default execution space
    // (and potentially its host execution space) with default
    // parameters.  You may also pass in argc and argv, analogously to
    // MPI_Init().  It reads and removes command-line arguments that
    // start with "--kokkos-".
    Kokkos::initialize(argc, argv);
    {
        //static constexpr int n = 100;
        S s0;
        S s1 = std::move(s0);
        S s2(s0);
        S s3(std::move(s2));

        ViewVectorD x("x", 5);
        ViewVectorD::HostMirror x_host = Kokkos::create_mirror_view(x);

        for (size_t i = 0; i < x_host.extent(0); i++) {
            do_something(i);
            x_host(i) = i;
        }

        // load data to device
        Kokkos::deep_copy(x, x_host);

        // make some nice stuff on device
        for (size_t i = 0; i < x_host.extent(0); i++) {
            do_something(i);
            x_host(i) = i;
        }
        ExecSpace ex;
        my_function(ex,x,2); // here we use our custom kernel on the device

        // get the results back to the host for Io stuff etc.
        Kokkos::deep_copy(x_host,x);

        for(size_t i = 0; i < x_host.extent(0); i++) {
            printf("value: %f\n",x_host[i]);
        }

        ViewVectorDHost v_host("v", 3);
        for (size_t i = 0; i < v_host.extent(0); i++) {
            do_something(i);
            v_host(i) = i;
        }

        ExecSpaceHost ex_host;
        my_function(ex_host,v_host,3); // here we use our custom kernel on the host

        for (size_t i = 0; i < v_host.extent(0); i++) {
            printf("value: %f\n",v_host[i]);
        }

        ViewMatrix3D x_mat("x_mat",3);
        ViewMatrix3D::HostMirror x_mat_host = Kokkos::create_mirror_view(x_mat);

        for(size_t n = 0; n < x_mat.extent(0); n++) {
            for (size_t m = 0; m < x_mat.extent(1) ; m++) {
                x_mat_host(n,m) = (ViewMatrix3D::value_type) n*m;
            }
        }

        Kokkos::deep_copy(x_mat,x_mat_host);
        calculate(ex,x_mat);
        Kokkos::deep_copy(x_mat_host,x_mat);

        //printf("Hello World on Kokkos execution space %s\n",
        //       typeid(ex).name());

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
                15, KOKKOS_LAMBDA(const int i) {
            // printf works in a CUDA parallel kernel; std::ostream does not.
            //printf("Hello from i = %i\n", i);

            ExampleProject::do_something(i);

        });
#endif

        Kokkos::fence();

        ExampleProject::do_something(100);
        // You must call finalize() after you are done using Kokkos.
    }
    Kokkos::finalize();
}