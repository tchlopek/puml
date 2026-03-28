// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <common/box.hpp>
#include <cst/node.hpp>
#include <token/is_token.hpp>
#include <token/range/element.hpp>
#include <token/range/view.hpp>

#include "result.hpp"

namespace puml::cst {

template<typename node_t, typename bracket_t, typename expr_t, bool early_error = true>
class bracketed {
public:
  static result try_make(const lex::token_view& tv) {
    auto i = tv.span().first;
    auto lb = tv.get_if(i, lex::is_token<bracket_t>{});
    if (!lb) {
      if constexpr (early_error) {
        return error {
          "could not find opening bracket: '" + std::string{ bracket_t::name } + "'",
          tv };
      } else {
        return {};
      }
    }
    auto rb = tv.find_closing_bracket(lex::token_element{ *lb, i });
    if (!rb) {
      return error {
        "could not find closing bracket for: '" + std::string{ bracket_t::name } + "'",
        tv };
    }

    auto expr = expr_t::try_make(tv.slice(i + 1, rb->index()));
    if (!expr) {
      return expr;
    }

    i += expr->get_len();
    i += 2;
    const auto len = i - tv.span().first;
    return node{ box{ node_t{ *lb, rb->get(), expr.unwrap() } }, len };
  }
};

}