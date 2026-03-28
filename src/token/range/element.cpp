#include "element.hpp"

namespace puml::lex {

token_element::token_element(const token& t, std::size_t index)
  : m_token{ t }
  , m_index{ index } {
}

std::size_t token_element::index() const {
  return m_index;
}

const token& token_element::get() const {
  return m_token;
}

}
