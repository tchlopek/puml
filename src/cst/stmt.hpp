// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <token/range/view_fwd.hpp>

#include "node.hpp"

namespace puml::cst {

class result;
struct stmt {
  node m_stmt;

  static result try_make(const lex::token_view& tv);
};

}
