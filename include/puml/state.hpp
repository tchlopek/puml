// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <string>
#include <vector>

namespace puml {

struct state {
  std::string name;
  std::vector<std::string> description;
  std::vector<const state*> children;
  const state* parent;
};

}
