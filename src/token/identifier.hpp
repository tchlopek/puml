#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "token_base.hpp"
#include "util/char_op.hpp"

namespace puml {

class identifier : public token_base<identifier> {
public:
  static constexpr std::string_view name = "identifier";
  using token_base::token_base;
  static std::optional<identifier>
  try_make(const std::string& str, std::size_t line, std::size_t pos) {
    if ((pos = str.find_first_not_of(' ', pos)) == std::string::npos) {
      return {};
    }
    if (!isalpha(str[pos])) {
      return {};
    }
    std::size_t i = pos + 1;
    for (; i != str.length() && isalnum(str[i]); ++i) {
    }
    return identifier{ line, pos, i };
  }

  std::size_t len() const {
    return end - start;
  }
};

}
