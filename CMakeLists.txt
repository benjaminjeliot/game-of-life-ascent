# Copyright (c) 2025 Jim Eliot

cmake_minimum_required(VERSION 3.28)

project(
    "game-of-life-ascent"
    DESCRIPTION "Conway's Game Of Life with Ascent in-situ"
    LANGUAGES CXX C
    VERSION "0.1.0"
)

option(ENABLE_ASCENT "Enable Ascent in-situ visualization" ON)

find_package(mdspan REQUIRED)

find_package(MPI REQUIRED)

if(ENABLE_ASCENT)
  find_package(Ascent REQUIRED)
endif()

add_subdirectory(src)
