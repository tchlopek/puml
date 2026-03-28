// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <vector>

#include <token/token.hpp>

namespace puml::lex {

class token_view;
class token_range {
public:
  using iterator = std::vector<token>::const_iterator;

  token_range(std::vector<token>&& tokens);

  std::size_t size() const;
  iterator begin() const;
  iterator end() const;

private:
  std::vector<token> tokens;
};

}
