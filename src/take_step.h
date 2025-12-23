// Copyright 2025 (c) Jim Eliot

#ifndef GOL_SRC_STEP_H_
#define GOL_SRC_STEP_H_

#include "gol/World.h"

namespace gol {

//! @brief Take one step.
auto take_step(gol::World &world, int step_number) -> void;

}  // namespace gol

#endif  // GOL_SRC_STEP_H_
