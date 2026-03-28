#pragma once

#include <cst/includes.hpp>
#include <cst/node.hpp>
#include <token/range/view.hpp>

#include "result.hpp"

namespace puml::cst {

namespace detail {

template<typename T, typename... Ts>
result any(const token_view& tv) {
  if (auto node = T::try_make(tv); node || node.is_fatal()) {
    return node;
  }
  if constexpr (sizeof...(Ts) > 0) {
    return any<Ts...>(tv);
  } else {
    return {};
  }
}

}

template<typename... Ts>
struct any {
  static result try_make(const token_view& tv) {
    return detail::any<Ts...>(tv);
  }
};

}
