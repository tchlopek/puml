#pragma once

#include <string>

#include "range/range.hpp"

namespace puml::lex {

class result {
public:
  explicit result(const std::string& error_msg);
  explicit result(token_range range);

  const token_range& get_range() const;
  const std::string& get_error() const;

  operator bool() const;

private:
  token_range m_range;
  std::string m_error_message;
};

}
