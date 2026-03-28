#pragma once

#include <string_view>

#include "token_kw_base.hpp"

namespace puml {

class kw_state : public token_kw_base<kw_state> {
public:
  static constexpr std::string_view name = "state";
  using token_kw_base::token_kw_base;
};

}
