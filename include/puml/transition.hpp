// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <string>

namespace puml {

struct state;
struct transition {
  const state* source;
  const state* target;
  std::string text;
};

}
