#pragma once

#include <string_view>

#include "token_kw_base.hpp"

namespace puml::lex {

class kw_star : public token_kw_base<kw_star> {
public:
  static constexpr std::string_view name = "[*]";
  using token_kw_base::token_kw_base;
};

}
