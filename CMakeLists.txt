cmake_minimum_required(VERSION 3.19)

project(ExampleProject VERSION 1.0.3)

# link in kokkos lib
find_package(Kokkos REQUIRED HINTS ./libs/kokkos/lib/cmake)

# include the directory of the project headers
include_directories(./include)

add_subdirectory(./src)

# check the kokkos backend of the installed kokkos lib
if(Kokkos_ENABLE_CUDA)
    message("-- We have a Cuda backend")
elseif(Kokkos_ENABLE_OPENMP)
    message("-- We have a OpenMP backend")
endif()

message("-- Our current compiler is: ${CMAKE_CXX_COMPILER}")

if(KOKKOS_DEBUG)
    message("-- Kokkos is in debug")
endif()
if(CMAKE_CXX_STANDARD)
    message("-- Our CXX standard is: ${CMAKE_CXX_STANDARD}")
endif()