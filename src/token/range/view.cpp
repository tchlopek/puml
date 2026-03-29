// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#include <algorithm>
#include <optional>
#include <stack>

#include <token/is_token.hpp>

#include "element.hpp"
#include "range.hpp"
#include "view.hpp"

namespace puml::lex {

namespace {

template<typename lhs, typename rhs>
std::optional<token_element> find_closing_bracket(const token_view& tv, const token_element& elem) {
  auto paren_view = tv.slice_left(elem.index());
  std::stack<token_element> tq;

  while (const auto p = paren_view.find_any_left(is_token<lhs, rhs>{})) {
    if (p->get().template is<lhs>()) {
      tq.push(*p);
    } else if (tq.pop(); tq.empty()) {
      return p;
    }
    paren_view = paren_view.slice_left(p->index() + 1);
  }

  return {};
}

bool is_between_brackets(const token_view& tv, const token_element& te) {
  auto tvtmp = tv;
  const auto get_left = [&] {
    return tvtmp.find_any_left(is_token<l_brace>{});
  };
  for (auto l = get_left(); l && l->index() < te.index(); l = get_left()) {
    if (const auto r = tvtmp.find_closing_bracket(*l)) {
      if (r->index() > te.index()) {
        return true;
      }
      tvtmp = tvtmp.slice_left(r->index());
    } else {
      break;
    }
  }
  return false;
}

template<typename fn_t>
std::optional<token_element> find_global(const token_view& tv, const fn_t& fn) {
  auto view = tv;
  while (const auto elem = fn(view)) {
    if (!is_between_brackets(tv, *elem)) {
      return elem;
    }
    view = view.slice_right(elem->index());
  }
  return {};
}

}

token_view::token_view(const token_range& rng)
  : token_view{ &rng, 0, rng.size() } {
}

token_view::token_view(const token_range* rng, std::size_t first, std::size_t last)
  : range_ptr{ rng }
  , first{ first }
  , last{ last } {
}

std::optional<token> token_view::get_if(std::size_t index, const pred_t& pred)
  const {
  if (!in_range(index)) {
    return {};
  }

  const auto iter = range_ptr->begin() + index;
  return pred(*iter) ? std::optional{ *iter } : std::nullopt;
}

std::optional<token_element> token_view::find_any_left(const token_view::pred_t& pred) const {
  const auto iter = std::find_if(
    range_ptr->begin() + first,
    range_ptr->begin() + last,
    pred
  );
  const std::size_t index = std::distance(range_ptr->begin(), iter);
  return in_range(index) ? std::optional{ token_element{ *iter, index } }
                         : std::nullopt;
}

std::optional<token_element> token_view::find_any_right(const token_view::pred_t& pred) const {
  std::reverse_iterator b{ range_ptr->begin() + last };
  std::reverse_iterator e{ range_ptr->begin() + first };

  const auto iter = std::find_if(b, e, pred);
  const std::size_t index = std::distance(range_ptr->begin(), iter.base()) - 1;
  return in_range(index) ? std::optional{ token_element{ *iter, index } }
                         : std::nullopt;
}

std::optional<token_element> token_view::find_global_left(const token_view::pred_t& pred) const {
  return find_global(*this, [&](const token_view& tv) {
    return tv.find_any_left(pred);
  });
}

std::optional<token_element> token_view::find_global_right(const token_view::pred_t& pred) const {
  return find_global(*this, [&](const token_view& tv) {
    return tv.find_any_right(pred);
  });
}

std::optional<token_element> token_view::find_closing_bracket(const token_element& elem) const {
  if (elem.get().is<l_brace>()) {
    return ::puml::lex::find_closing_bracket<l_brace, r_brace>(*this, elem);
  } else {
    return {};
  }
}

std::pair<std::size_t, std::size_t> token_view::span() const {
  return { first, last };
}

token_view token_view::slice(std::size_t b, std::size_t e) const {
  b = std::clamp(b, first, last);
  e = std::clamp(e, first, last);
  return token_view{ range_ptr, std::min(b, e), std::max(b, e) };
}

token_view token_view::slice_left(std::size_t f) const {
  return slice(f, last);
}

token_view token_view::slice_right(std::size_t e) const {
  return slice(first, e);
}

std::size_t token_view::size() const {
  return last - first;
}

token_view::iterator token_view::begin() const {
  return range_ptr->begin() + first;
}

token_view::iterator token_view::end() const {
  return range_ptr->begin() + last;
}

std::string token_view::get_line_string(const std::vector<std::string>& text) const {
  auto line = std::string{};

  if (size() == 0) {
    return line;
  }

  const auto span_fn = [](const auto& t){ return t.span(); };
  auto prev_end = begin()->map(span_fn).second;
  line = begin()->str(text);

  for (auto it = std::next(begin()); it != end(); ++it) {
    const auto span = it->map(span_fn);
    line += std::string(span.first - prev_end, ' ') + it->str(text);
    prev_end = span.second;
  }

  return line;
}

bool token_view::in_range(std::size_t index) const {
  return index >= first && index < last;
}

}
