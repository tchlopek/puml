// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#include "result.hpp"

namespace puml::lex {

result::result(const std::string& error_msg)
  : m_range{ {} }
  , m_error_message{ error_msg }
{}

result::result(token_range range)
  : m_range{ std::move(range) }
  , m_error_message{}
{}

const token_range& result::get_range() const {
  return m_range; 
}

const std::string& result::get_error() const {
  return m_error_message;
}

result::operator bool() const {
  return m_error_message.empty();
}

}
