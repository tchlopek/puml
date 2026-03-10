#pragma once

#include <string_view>

#include "token_kw_base.hpp"

namespace tkn {
class kw_arrow_left : public token_kw_base<kw_arrow_left> {
public:
  static constexpr std::string_view name = "-left->";
  using token_kw_base::token_kw_base;
};
}    // namespace tkn
