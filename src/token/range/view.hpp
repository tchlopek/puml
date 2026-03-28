// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <functional>
#include <optional>
#include <utility>

#include "range.hpp"

namespace puml::lex {

class token_element;
class token_view {
public:
  using iterator = token_range::iterator;
  using pred_t = std::function<bool(const token&)>;

  explicit token_view(const token_range&);

  std::optional<token> get_if(std::size_t, const pred_t&) const;
  std::optional<token_element> find_any_left(const pred_t&) const;
  std::optional<token_element> find_any_right(const pred_t&) const;
  std::optional<token_element> find_global_left(const pred_t&) const;
  std::optional<token_element> find_global_right(const pred_t&) const;
  std::optional<token_element> find_closing_bracket(const token_element&) const;
  std::pair<std::size_t, std::size_t> span() const;
  token_view slice(std::size_t, std::size_t) const;
  token_view slice_left(std::size_t) const;
  token_view slice_right(std::size_t) const;
  std::size_t size() const;
  iterator begin() const;
  iterator end() const;

private:
  token_view(const token_range*, std::size_t, std::size_t);

  bool in_range(std::size_t) const;

  const token_range* range_ptr;
  std::size_t first;
  std::size_t last;
};

}
