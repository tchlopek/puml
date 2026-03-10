#pragma once

#include <string_view>

#include "token_kw_base.hpp"

namespace tkn {
class kw_arrow_up : public token_kw_base<kw_arrow_up> {
public:
  static constexpr std::string_view name = "-up->";
  using token_kw_base::token_kw_base;
};
}    // namespace tkn
