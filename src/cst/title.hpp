// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <token/range/view.hpp>

namespace puml::cst {

class result;
struct title {
  lex::token_view title_strings;

  static result try_make(const lex::token_view& tv);
};

}
