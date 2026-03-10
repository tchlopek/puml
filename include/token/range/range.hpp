#pragma once

#include <vector>

#include <token/token.hpp>

namespace tkn {
class view;
class range {
public:
  using iterator = std::vector<tkn::token>::const_iterator;

  range(std::vector<tkn::token>&& tokens);

  std::size_t size() const;
  iterator begin() const;
  iterator end() const;

private:
  std::vector<tkn::token> tokens;
};
}    // namespace tkn
