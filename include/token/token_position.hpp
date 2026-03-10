#pragma once

#include <cstddef>

struct token_position {
  std::size_t line_num;
  std::size_t start;
  std::size_t end;
};
