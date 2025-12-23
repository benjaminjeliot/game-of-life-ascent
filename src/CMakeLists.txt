# Copyright (c) 2025 Jim Eliot

add_subdirectory(gol)

add_executable(game-of-life advance.cpp main.cpp take_step.cpp)

target_compile_features(game-of-life PRIVATE cxx_std_23)

target_include_directories(game-of-life PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(game-of-life PRIVATE std::mdspan gol_core
                                           ascent::ascent_mpi)
