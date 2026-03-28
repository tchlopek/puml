#pragma once

#include <cctype>

namespace puml {

inline bool isalpha(const char c) noexcept {
  return std::isalpha(c) != 0 || c == '_';
}

inline bool isalnum(const char c) noexcept {
  return std::isalnum(c) != 0 || c == '_';
}

}
