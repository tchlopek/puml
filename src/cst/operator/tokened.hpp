// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <cst/node.hpp>
#include <cst/token.hpp>
#include <token/is_token.hpp>
#include <token/range/view.hpp>

#include "result.hpp"

namespace puml::cst {

template<typename tok_t>
struct tokened {
  static result try_make(const lex::token_view& tv) {
    const auto tok = tv.get_if(tv.span().first, lex::is_token<tok_t>{});
    return tok
      ? result{ node{ box{ token{ *tok } }, 1 } }
      : error{ "missing token '" + std::string{ tok_t::name } + "'", tv };
  }
};

template<typename tok_t, typename... tok_ts>
struct tokened_single {
  static result try_make(const lex::token_view& tv) {
    const auto tok = tv.get_if(tv.span().first, lex::is_token<tok_t, tok_ts...>{});
    return tok && tv.size() == 1
           ? result{ node{ box{ token{ *tok } }, 1 } }
           : error{ "missing token '" + std::string{ tok_t::name } + "'", tv };
  }
};

}
