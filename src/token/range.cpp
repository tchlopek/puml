#include <token/range/range.hpp>
#include <token/range/view.hpp>

namespace tkn {
range::range(std::vector<tkn::token>&& tokens)
  : tokens{ std::move(tokens) } {
}

std::size_t range::size() const {
  return tokens.size();
}

range::iterator range::begin() const {
  return tokens.begin();
}

range::iterator range::end() const {
  return tokens.end();
}
}    // namespace tkn
