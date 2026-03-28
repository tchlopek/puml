// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "token_base.hpp"

namespace puml::lex {

class text : public token_base<text> {
public:
  static constexpr std::string_view name = "text";
  using token_base::token_base;
  static std::optional<text>
  try_make(const std::string& str, std::size_t line, std::size_t pos) {
    if ((pos = str.find_first_not_of(' ', pos)) == std::string::npos) {
      return {};
    }
    if (str[pos] != ':') {
      return {};
    }
    // store end as exclusive index (end of line)
    return text{ line, pos, str.size() };
  }

  std::size_t len() const {
    return end - start;
  }
};

}
