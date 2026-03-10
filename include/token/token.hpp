#pragma once

#include <string>
#include <variant>
#include <vector>

#include "identifier.hpp"
#include "kw_arrow_double.hpp"
#include "kw_arrow_down.hpp"
#include "kw_arrow_left.hpp"
#include "kw_arrow_right.hpp"
#include "kw_arrow_single.hpp"
#include "kw_arrow_up.hpp"
#include "l_brace.hpp"
#include "r_brace.hpp"
#include "text.hpp"


namespace tkn {
class token {
public:
  using type = std::variant<
    kw_arrow_double,
    kw_arrow_down,
    kw_arrow_left,
    kw_arrow_right,
    kw_arrow_single,
    kw_arrow_up,
    l_brace,
    r_brace,
    text,
    identifier>;

  template<typename token_t>
  explicit token(token_t&& tkn)
    : storage{ std::forward<token_t>(tkn) } {
  }

  template<typename... token_ts>
  bool is() const {
    return (std::holds_alternative<token_ts>(storage) || ...);
  }

  template<typename func_t>
  decltype(auto) map(func_t&& fn) const {
    return std::visit(std::forward<func_t>(fn), storage);
  }

  std::string str(const std::vector<std::string>& text) const {
    return map([&](const auto& t) {
      const auto [first, len] = t.span();
      return text[t.line()].substr(first, len);
    });
  }

  std::string_view name() const {
    const auto get_name = [](auto& t) {
      return std::remove_cv_t<std::remove_reference_t<decltype(t)>>::name;
    };
    return std::visit(get_name, storage);
  }

private:
  type storage;
};
}
