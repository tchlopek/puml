#pragma once

#include <string_view>

#include "token_kw_base.hpp"

namespace puml::lex {

class kw_startuml : public token_kw_base<kw_startuml> {
public:
  static constexpr std::string_view name = "@startuml";
  using token_kw_base::token_kw_base;
};

}
