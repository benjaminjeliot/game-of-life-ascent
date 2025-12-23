// Copyright (c) 2025 Jim Eliot

#include "gol/ascent_insitu.h"

#include <mpi.h>

#include <ascent.hpp>
#include <iostream>

#include "gol/World.h"

static ascent::Ascent ascent_instance;

namespace gol {

auto ascent_insitu_initialize() -> void {
  // Initialize Ascent
  conduit::Node ascent_options;
  ascent_options["mpi_comm"] = MPI_Comm_c2f(MPI_COMM_WORLD);
  ascent_options["runtime/type"] = "ascent";
  ascent_options["runtime/backend"] = "serial";
  ascent_options["web/stream"] = "false";
  ascent_options["pipeline/type"] = "vtkm";
  ascent_options["default_dir"] = "images";

  ascent_instance.open(ascent_options);
}

auto ascent_insitu_execute(gol::World world, int step_number) -> void {
  // Get MPI size and rank
  int mpi_size{-1};
  int mpi_rank{-1};
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

  conduit::Node sim_data;
  sim_data["state/time"] = static_cast<conduit::float64>(step_number);
  sim_data["state/domain_id"] = static_cast<conduit::uint64>(mpi_rank);
  sim_data["state/cycle"] = static_cast<conduit::uint64>(step_number);

  auto world_mds = world.GetWorldMDSpan();

  auto n_x_cells = world.GetWorldMDSpan().extent(0);
  auto n_y_cells = world.GetWorldMDSpan().extent(1);
  std::size_t n_x_nodes{n_x_cells + 1};
  std::size_t n_y_nodes{n_y_cells + 1};

  // Create uniform coordset
  sim_data["coordsets/coords/type"] = "uniform";
  sim_data["coordsets/coords/dims/i"] = n_x_nodes;
  sim_data["coordsets/coords/dims/j"] = n_y_nodes;
  sim_data["coordsets/coords/origin"] = {0.0, 0.0, 0.0};
  sim_data["coordsets/coords/spacing"] = {1.0, 1.0, 1.0};

  // Create uniform topology
  sim_data["topologies/topo/coordset"] = "coords";
  sim_data["topologies/topo/type"] = "uniform";
  sim_data["topologies/topo/elements/origin"] = {0, 0, 0};

  // Create a field named "alive"
  sim_data["fields/alive/association"] = "element";
  sim_data["fields/alive/topology"] = "topo";
  sim_data["fields/alive/values"].set_external_int32_ptr(
      world_mds.data_handle(), world_mds.size());

  // make sure that the mesh we created conforms to the blueprint
  conduit::Node verify_info;
  if (!conduit::blueprint::mesh::verify(sim_data, verify_info)) {
    std::cout << "Mesh verify failed\n";
    std::cout << verify_info.to_yaml() << std::endl;
    ;
    CONDUIT_INFO("blueprint verify failed!" + verify_info.to_json());
  } else {
    // std::cout << "Mesh verify success!\n";
    // CONDUIT_INFO("blueprint verify succeeded");
  }

  ascent_instance.publish(sim_data);

  conduit::Node insitu_actions;

  ascent_instance.execute(insitu_actions);
}

auto ascent_insitu_finalize() -> void {
  // Finalize Ascent
  std::cout << "gol::finalize -- finalizing Ascent" << std::endl;
  ascent_instance.close();
}

}  // namespace gol
