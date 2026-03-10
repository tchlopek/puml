#pragma once

#include <functional>
#include <optional>
#include <utility>

#include "range.hpp"

namespace tkn {
class element;
class view {
public:
  using iterator = range::iterator;
  using pred_t = std::function<bool(const tkn::token&)>;

  explicit view(const range&);

  std::optional<tkn::token> get_if(std::size_t, const pred_t&) const;
  std::optional<element> find_any_left(const pred_t&) const;
  std::optional<element> find_any_right(const pred_t&) const;
  std::optional<element> find_global_left(const pred_t&) const;
  std::optional<element> find_global_right(const pred_t&) const;
  std::optional<element> find_closing_bracket(const element&) const;
  std::pair<std::size_t, std::size_t> span() const;
  view slice(std::size_t, std::size_t) const;
  view slice_left(std::size_t) const;
  view slice_right(std::size_t) const;
  std::size_t size() const;
  iterator begin() const;
  iterator end() const;

private:
  view(const range*, std::size_t, std::size_t);

  bool in_range(std::size_t) const;

  const range* range_ptr;
  std::size_t first;
  std::size_t last;
};
}    // namespace tkn
