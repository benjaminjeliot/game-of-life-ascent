// Copyright (c) 2025 Jim Eliot

#ifndef GOL_SOURCE_GOL_WORLD_H_
#define GOL_SOURCE_GOL_WORLD_H_

#include <cstddef>
#include <experimental/mdspan>
#include <memory>

namespace gol {

using world_extents = std::experimental::extents<size_t, std::dynamic_extent,
                                                 std::dynamic_extent>;
using world_mdspan_type = std::experimental::mdspan<int, gol::world_extents>;

class World {
 public:
  //! @brief Constructor.
  World(size_t n_x_cells, size_t n_y_cells);

  //! @brief Get world mdspan.
  auto GetWorldMDSpan() -> world_mdspan_type;

  //! @brief Get temp world mdspan.
  auto GetNextStateMDSpan() -> world_mdspan_type;

  //! @brief Swap mdspan for world and next state.
  auto SwapWorldAndNextState() -> void;

 private:
  std::size_t n_x_cells_{0};
  std::size_t n_y_cells_{0};

  std::shared_ptr<int[]> world_sp_{nullptr};
  std::shared_ptr<int[]> next_state_sp_{nullptr};

  world_mdspan_type world_mds_;
  world_mdspan_type next_state_mds_;
};

}  // namespace gol

#endif  // GOL_SOURCE_GOL_WORLD_H_
