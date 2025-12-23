// Copyright (c) 2025 Jim Eliot

#include "initialize.h"

#include <mpi.h>

#include <ascent.hpp>
#include <execution>
#include <experimental/mdspan>
#include <iostream>
#include <memory>
#include <random>
#include <ranges>

#include "gol/World.h"
#include "gol/ascent_insitu.h"

namespace gol {

auto initialize(int *argc, char ***argv) -> gol::World {
  std::cout << "Initializing" << std::endl;

  // Initialize MPI
  MPI_Init(argc, argv);
  int mpi_size{-1};
  int mpi_rank{-1};
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
  std::cout << "initialize -- mpi_size: " << mpi_size << std::endl;
  std::cout << "initialize -- mpi_rank: " << mpi_rank << std::endl;

  std::size_t n_x_cells{200};
  std::size_t n_y_cells{200};

  gol::ascent_insitu_initialize();

  gol::World world(n_x_cells, n_y_cells);

  return world;
}

}  // namespace gol
