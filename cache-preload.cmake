# Copyright (c) 2025 Jim Eliot

set(ENABLE_ASCENT
    ON
    CACHE BOOL "Enable Ascent in-situ visualization")

set(MDSPAN_PREFIX
    ""
    PATH
    "Kokkos mdspan prefix")

set(ASCENT_PREFIX
    ""
    PATH
    "Ascent prefix"
)

set(MPIEXEC_EXECUTABLE
    ""
    CACHE FILEPATH "mpiexec executable")

set(CMAKE_PREFIX_PATH
    ${MDSPAN_PREFIX} ${ASCENT_PREFIX}
    CACHE PATH "CMake prefix path")
