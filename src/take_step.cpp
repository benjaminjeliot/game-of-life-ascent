// Copyright (c) 2025 Jim Eliot

#include "take_step.h"

#include <execution>
#include <iostream>
#include <ranges>

#include "gol/World.h"

namespace gol {

auto take_step(gol::World &world, int step_number) -> void {
  std::cout << "Executing step " << step_number << std::endl;

  auto world_mds = world.GetWorldMDSpan();
  auto next_state_mds = world.GetNextStateMDSpan();

  auto n_x_cells = world_mds.extent(0);
  auto n_y_cells = world_mds.extent(1);
  auto n_cells = world_mds.size();

  // Our indices go from the second element to the second to last element
  auto x_indices = std::views::iota(size_t(1), n_x_cells - 1);
  auto y_indices = std::views::iota(size_t(1), n_y_cells - 1);

  std::for_each(
      std::execution::par_unseq, y_indices.begin(), y_indices.end(),
      [=, &world_mds, &next_state_mds](std::size_t i) {
        std::for_each(
            std::execution::par_unseq, x_indices.begin(), x_indices.end(),
            [=, &world_mds, &next_state_mds](std::size_t j) {
              std::size_t x = i / n_y_cells;
              std::size_t y = i % n_y_cells;
              int n_neighbours = world_mds[i - 1, j - 1] + world_mds[i - 1, j] +
                                 world_mds[i - 1, j + 1] + world_mds[i, j - 1] +
                                 world_mds[i, j + 1] + world_mds[i + 1, j - 1] +
                                 world_mds[i + 1, j] + world_mds[i + 1, j + 1];
              int new_value{0};
              if (n_neighbours < 2) {
                new_value = 0;
              } else if (n_neighbours == 2) {
                new_value = world_mds[i, j];
              } else if (n_neighbours == 3) {
                new_value = 1;
              } else if (n_neighbours >= 4) {
                new_value = 0;
              }

              // Set cell status of next state
              next_state_mds[i, j] = new_value;
            });
      });

  world.SwapWorldAndNextState();
}

}  // namespace gol
