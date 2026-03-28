#pragma once

#include <string_view>

#include "token_kw_base.hpp"

namespace puml::lex {
class kw_arrow_right : public token_kw_base<kw_arrow_right> {
public:
  static constexpr std::string_view name = "-right->";
  using token_kw_base::token_kw_base;
};

}
