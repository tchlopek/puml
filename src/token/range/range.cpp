// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#include "range.hpp"
#include "view.hpp"

namespace puml::lex {

token_range::token_range(std::vector<token>&& tokens)
  : tokens{ std::move(tokens) } {
}

std::size_t token_range::size() const {
  return tokens.size();
}

token_range::iterator token_range::begin() const {
  return tokens.begin();
}

token_range::iterator token_range::end() const {
  return tokens.end();
}

}
