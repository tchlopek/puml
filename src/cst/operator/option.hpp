// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <cst/null.hpp>
#include <token/range/view.hpp>

#include "result.hpp"

namespace puml::cst {

template<typename node_t>
struct option {
  static result try_make(const lex::token_view& tv) {
    if (tv.size() == 0) {
      return node{ box{ null{} }, 0 };
    }

    auto n = node_t::try_make(tv);
    return n || n.is_fatal() ? std::move(n) : node{ box{ null{} }, 0 };
  }
};

}
