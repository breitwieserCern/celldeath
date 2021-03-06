// -----------------------------------------------------------------------------
//
// Copyright (C) The BioDynaMo Project.
// All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------
#ifndef CELLDEATH_H_
#define CELLDEATH_H_

#include "biodynamo.h"

namespace bdm {

struct RemoveFromSimulationBM : public BaseBiologyModule {
  RemoveFromSimulationBM() : BaseBiologyModule(gAllBmEvents) {}

  template <typename T>
  void Run(T* cell) {
    if (cell->GetDiameter() < 35) {
      cell->ChangeVolume(400);
    } else {
      cell->RemoveFromSimulation();
    }
  }

  ClassDefNV(RemoveFromSimulationBM, 1);
};

// Define compile time parameter
template <typename Backend>
struct CompileTimeParam : public DefaultCompileTimeParam<Backend> {
  using BiologyModules = Variant<RemoveFromSimulationBM>;
};

inline int Simulate(int argc, const char** argv) {
  Simulation<> simulation(argc, argv);

  // Define initial model - in this example: single cell at origin
  auto* rm = simulation.GetResourceManager();
  auto&& cell = rm->New<Cell>(30);
  cell.AddBiologyModule(RemoveFromSimulationBM());

  // Run simulation for one timestep
  simulation.GetScheduler()->Simulate(2000);

  std::cout << "Simulation completed successfully!" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // CELLDEATH_H_
