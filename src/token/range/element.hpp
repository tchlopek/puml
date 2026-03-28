#pragma once

#include <token/token.hpp>

namespace puml::lex {

class token_element {
public:
  token_element(const token&, std::size_t);

  std::size_t index() const;
  const token& get() const;

private:
  token m_token;
  std::size_t m_index;
};

}
