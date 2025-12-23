// Copyright (c) 2025 Jim Eliot

#ifndef GOL_SOURCE_ASCENT_INSITU_H_
#define GOL_SOURCE_ASCENT_INSITU_H_

#include <ascent.hpp>

#include "gol/World.h"

namespace gol {

auto ascent_insitu_initialize() -> void;

auto ascent_insitu_execute(gol::World world, int step_number) -> void;

auto ascent_insitu_finalize() -> void;

}  // namespace gol

#endif  // GOL_SOURCE_ASCENT_INSITU_H_
