// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <cstddef>

namespace puml::lex {

struct token_position {
  std::size_t line_num;
  std::size_t start;
  std::size_t end;
};

}
