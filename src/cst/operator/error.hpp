// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <string>

#include <token/range/view.hpp>

namespace puml::cst {

struct error {
  std::string message;
  lex::token_view tv;
};

}
