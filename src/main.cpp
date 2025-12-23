// Copyright (c) 2025 Jim Eliot

#include <iostream>

#include "advance.h"
#include "gol/World.h"
#include "gol/finalize.h"
#include "gol/initialize.h"

auto main(int argc, char *argv[]) -> int {
  std::cout << "Conway's Game Of Life" << std::endl;

  // Initialize world
  auto world = gol::initialize(&argc, &argv);

  // Advance world
  gol::advance(world);

  // Finalize world
  gol::finalize();

  return 0;
}
