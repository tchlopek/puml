#pragma once

#include <string_view>

#include "token_base.hpp"

namespace tkn {
class r_brace : public token_base<r_brace> {
public:
  static constexpr std::string_view name = "}";
  using token_base::token_base;
};
}    // namespace tkn
