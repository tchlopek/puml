// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#include <token/range/view.hpp>
#include <token/range/element.hpp>
#include <token/kw_title.hpp>

#include "operator/result.hpp"

#include "title.hpp"

namespace puml::cst {

static constexpr auto line = [](const auto& t) {
  return t.line();
};

result title::try_make(const lex::token_view& tv) {
  const auto begin_tok = tv.begin();
  if (!begin_tok->is<lex::kw_title>()) {
    return {};
  }

  const auto current_line = begin_tok->map(line);
  const auto end_of_current_line = tv.find_any_left([&](const lex::token& t) {
    return t.map(line) != current_line;
  });

  if (!end_of_current_line) {
    return error { "invalid title name", tv };
  }

  const auto title_view = tv.slice(tv.span().first + 1, end_of_current_line->index());
  return node{ box{ title{ title_view } }, title_view.size() + 1 };
}

}
