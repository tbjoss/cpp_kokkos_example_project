#!/bin/bash

# setup kokkos install dir
export KOKKOS_INSTALL_DIR="$(pwd)/libs/kokkos"
echo ${KOKKOS_INSTALL_DIR}

# setup kokkos backend (Serial, OpenMP, Cuda)
export KOKKOS_BACKEND="Cuda"

# define build type
export BUILD_TYPE="Debug"

# select compiler (g++ clang++-12)
export CXX=clang++-12

cd scripts

./install_kokkos.sh

cd ..
