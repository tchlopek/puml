// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <token/range/view.hpp>

#include "result.hpp"

namespace puml::cst {

template<typename node_t>
struct try_match {
  static result try_make(const lex::token_view& tv) {
    auto n = node_t::try_make(tv);
    return n ? std::move(n) : result{};
  }
};

}

