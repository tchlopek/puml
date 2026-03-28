#pragma once

#include <optional>
#include <string>
#include <utility>

#include "token_position.hpp"

namespace puml {

template<typename token_t>
class token_base : protected token_position {
  const token_t& deriv() const {
    return static_cast<const token_t&>(*this);
  }

public:
  token_base(std::size_t line_num, std::size_t start, std::size_t end)
    : token_position{ line_num, start, end } {
  }

  static std::optional<token_t>
  try_make(const std::string& str, std::size_t line, std::size_t pos) {
    if ((pos = str.find_first_not_of(' ', pos)) == std::string::npos) {
      return {};
    }
    if (str.substr(pos, token_t::len()) == token_t::name) {
      return token_t{ line, pos, pos + token_t::len() };
    }
    return {};
  }

  static std::size_t len() {
    return token_t::name.length();
  }

  std::pair<std::size_t, std::size_t> span() const {
    return { start, end };
  }

  std::size_t line() const {
    return line_num;
  }
};

}
