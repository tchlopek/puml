#pragma once

#include "token.hpp"

namespace puml {

template<typename... token_ts>
struct is_token {
  bool operator()(const token& t) const {
    return t.is<token_ts...>();
  }
};

}
