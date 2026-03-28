// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <string_view>

#include "token_base.hpp"

namespace puml::lex {

class r_brace : public token_base<r_brace> {
public:
  static constexpr std::string_view name = "}";
  using token_base::token_base;
};

}
