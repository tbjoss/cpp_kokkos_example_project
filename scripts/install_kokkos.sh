#!/bin/bash

rm -rfv ${KOKKOS_INSTALL_DIR}

# load master version of bitpit
#echo "Downloading kokkos from github"
#git clone https://github.com/kokkos/kokkos.git
cd kokkos

# make the install dir if it does not exist already
echo "Make kokkos install dir: " ${KOKKOS_INSTALL_DIR}
mkdir -p ${KOKKOS_INSTALL_DIR}

# make build folder
rm -rfv build
mkdir build
cd build

# config the kokkos build
echo "Kokkos backend is set to: " ${KOKKOS_BACKEND}

# config kokkos for serial build
if [ "$KOKKOS_BACKEND" == "Serial" ]; then
  cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_CXX_COMPILER=${CXX} -DCMAKE_INSTALL_PREFIX=${KOKKOS_INSTALL_DIR} -DKokkos_CXX_STANDARD=17 .. /
fi

#config kokkos for OpenMP build
if [ "$KOKKOS_BACKEND" == "OpenMP" ]; then
  cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_CXX_COMPILER=${CXX} -DCMAKE_INSTALL_PREFIX=${KOKKOS_INSTALL_DIR} -DKokkos_CXX_STANDARD=17 -DKokkos_ENABLE_OPENMP=ON .. /
fi


# config kokkos for Cuda build
if [ "$KOKKOS_BACKEND" == "Cuda" ]; then
  cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_CXX_COMPILER=${CXX} -DCMAKE_INSTALL_PREFIX=${KOKKOS_INSTALL_DIR} -DKokkos_CXX_STANDARD=17 -DKokkos_ENABLE_CUDA=ON -DKokkos_ENABLE_CUDA_CONSTEXPR=ON -DKokkos_ENABLE_CUDA_LAMBDA=ON -DKokkos_ARCH_TURING75=ON .. /
fi

# build kokkos
cmake --build . -- -j10
make install
cd ..
