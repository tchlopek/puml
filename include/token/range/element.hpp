#pragma once

#include <token/token.hpp>

namespace tkn {
class element {
public:
  element(const token&, std::size_t);

  std::size_t index() const;
  const token& get() const;

private:
  token m_token;
  std::size_t m_index;
};
}    // namespace tkn
