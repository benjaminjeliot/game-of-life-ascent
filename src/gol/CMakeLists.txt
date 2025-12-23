# Copyright (c) 2025 Jim Eliot

add_library(gol_core World.cpp ascent_insitu.cpp initialize.cpp finalize.cpp)

target_compile_features(gol_core PRIVATE cxx_std_23)

target_include_directories(gol_core PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(gol_core PRIVATE std::mdspan MPI::MPI_CXX
                                       ascent::ascent_mpi)
