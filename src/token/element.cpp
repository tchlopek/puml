#include <token/range/element.hpp>

namespace tkn {
element::element(const tkn::token& token, std::size_t index)
  : m_token{ token }
  , m_index{ index } {
}

std::size_t element::index() const {
  return m_index;
}

const tkn::token& element::get() const {
  return m_token;
}
}    // namespace tkn
