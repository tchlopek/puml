#pragma once

#include <string_view>

#include "token_kw_base.hpp"

namespace puml {

class kw_arrow_double : public token_kw_base<kw_arrow_double> {
public:
  static constexpr std::string_view name = "-->";
  using token_kw_base::token_kw_base;
};

}
