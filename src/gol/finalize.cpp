// Copyright (c) 2025 Jim Eliot

#include "gol/finalize.h"

#include <mpi.h>

#include <iostream>

#include "gol/ascent_insitu.h"

namespace gol {

auto finalize() -> void {
  // Finalize simulation

  // Finalize Ascent
  gol::ascent_insitu_finalize();

  // Finalize MPI
  MPI_Finalize();
}

}  // namespace gol
