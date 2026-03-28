// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include "token_base.hpp"
#include "util/char_op.hpp"

namespace puml::lex {

template<typename token_t>
class token_kw_base : public token_base<token_t> {
public:
  using token_base<token_t>::token_base;

  static std::optional<token_t>
  try_make(const std::string& str, std::size_t line, std::size_t pos) {
    if ((pos = str.find_first_not_of(' ', pos)) == std::string::npos) {
      return {};
    }

    const auto end_pos = pos + token_t::len();
    if (end_pos == str.length() || (end_pos < str.length() && !isalnum(str[end_pos]))) {
      return str.substr(pos, token_t::len()) == token_t::name
        ? std::optional{ token_t{ line, pos, end_pos } }
        : std::nullopt;
    }

    return {};
  }
};

}
