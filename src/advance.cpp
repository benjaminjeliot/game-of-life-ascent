// Copyright (c) 2025 Jim Eliot

#include "advance.h"

#include <execution>
#include <iostream>
#include <ranges>

#include "gol/World.h"
#include "gol/ascent_insitu.h"
#include "take_step.h"

namespace gol {

auto advance(gol::World &world) -> void {
  // Time steps
  int timestep_range[] = {0, 500};

  // Iterate over timesteps
  std::ranges::for_each(std::views::iota(timestep_range[0], timestep_range[1]),
                        [&](int timestep) {
                          gol::take_step(world, timestep);

                          gol::ascent_insitu_execute(world, timestep);
                        });
}

}  // namespace gol
