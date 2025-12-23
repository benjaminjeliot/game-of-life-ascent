// Copyright (c) 2025 Jim Eliot

#include "gol/World.h"

#include <cstddef>
#include <execution>
#include <experimental/mdspan>
#include <iostream>
#include <random>
#include <ranges>

namespace gol {

World::World(std::size_t n_x_cells, std::size_t n_y_cells)
    : n_x_cells_(n_x_cells), n_y_cells_(n_y_cells) {
  // Number of cells -- x_cells * y_cells
  std::size_t n_cells{n_x_cells * n_y_cells};

  world_sp_ = std::shared_ptr<int[]>(new int[n_cells]);

  world_mds_ = std::experimental::mdspan<int, world_extents>(
      world_sp_.get(), n_x_cells_, n_y_cells_);

  auto cell_indices = std::views::iota(size_t(0), n_cells);

  auto &world_mds{world_mds_};

  // Initialize cells randomly
  std::for_each(
      std::execution::par_unseq, cell_indices.begin(), cell_indices.end(),
      [=, &n_x_cells, &n_y_cells, &world_mds](std::size_t i) {
        size_t x = i / n_y_cells;
        size_t y = i % n_y_cells;

        std::int32_t status{rand() % 2};
        // std::int32_t status{rand() & 1};

        std::random_device rd;   // a seed source for the random number engine
        std::mt19937 gen(rd());  // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(0, 1);
        auto random_value = distrib(gen);
        world_mds[x, y] = random_value;
      });

  // Create temp array
  next_state_sp_ = std::shared_ptr<int[]>(new int[n_cells]);
  next_state_mds_ = std::experimental::mdspan<int, world_extents>(
      next_state_sp_.get(), n_x_cells_, n_y_cells_);
  auto &next_state_mds{next_state_mds_};
  // Initialize temp array to zeroes
  std::for_each(
      std::execution::par_unseq, cell_indices.begin(), cell_indices.end(),
      [=, &n_x_cells, &n_y_cells, &next_state_mds](std::size_t i) {
        size_t x = i / n_y_cells;
        size_t y = i % n_y_cells;

        std::int32_t status{rand() % 2};
        // std::int32_t status{rand() & 1};

        std::random_device rd;   // a seed source for the random number engine
        std::mt19937 gen(rd());  // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(0, 1);
        auto random_value = distrib(gen);
        next_state_mds[x, y] = random_value;
      });
}

auto World::GetWorldMDSpan() -> world_mdspan_type { return world_mds_; }

auto World::GetNextStateMDSpan() -> world_mdspan_type {
  return next_state_mds_;
}

auto World::SwapWorldAndNextState() -> void {
  // Swap current and next state mdspans
  // auto temp_world = next_state_mds_;
  // next_state_mds_ = world_mds_;
  // world_mds_ = temp_world;

  // Swap shared pointers
  auto temp_sp = world_sp_;
  world_sp_ = next_state_sp_;
  next_state_sp_ = temp_sp;

  // Recreate mdspans
  world_mds_ = std::experimental::mdspan<int, world_extents>(
      world_sp_.get(), n_x_cells_, n_y_cells_);
  next_state_mds_ = std::experimental::mdspan<int, world_extents>(
      next_state_sp_.get(), n_x_cells_, n_y_cells_);
}

}  // namespace gol
