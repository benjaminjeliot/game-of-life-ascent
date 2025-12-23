// Copyright (c) 2025 Jim Eliot

#ifndef GOL_SOURCE_INITIALIZE_H_
#define GOL_SOURCE_INITIALIZE_H_

#include "gol/World.h"

namespace gol {

auto initialize(int *argc, char ***argv) -> gol::World;

}  // namespace gol

#endif  // GOL_SOURCE_INITIALIZE_H_
