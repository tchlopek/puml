// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <token/range/view_fwd.hpp>

#include "node.hpp"

namespace puml::cst {

class result;
struct scoped_state {
  node m_state_kw;
  node m_name_id;
  node m_scope_block;

  static result try_make(const lex::token_view& tv);
};

}