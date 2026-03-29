// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <string_view>

#include "token_kw_base.hpp"

namespace puml::lex {

class kw_title : public token_kw_base<kw_title> {
public:
  static constexpr std::string_view name = "title";
  using token_kw_base::token_kw_base;
};

}
