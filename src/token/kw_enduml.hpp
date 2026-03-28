#pragma once

#include <string_view>

#include "token_kw_base.hpp"

namespace puml::lex {

class kw_enduml : public token_kw_base<kw_enduml> {
public:
  static constexpr std::string_view name = "@enduml";
  using token_kw_base::token_kw_base;
};

}
