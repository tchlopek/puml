// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#include "result.hpp"

namespace puml::cst {

result::result()
  : m_storage{ std::vector<error>{} }
{}

result::result(error err)
  : m_storage{ std::vector{ std::move(err) } }
{}

result::result(node&& node)
  : m_storage{ std::move(node) }
{}

result::operator bool() const {
  return std::holds_alternative<node>(m_storage);
}

const node* result::operator->() const {
  return std::get_if<node>(&m_storage);
}

node&& result::unwrap() {
  return std::get<node>(std::move(m_storage));
}

bool result::is_fatal() const {
  const auto ptr = std::get_if<std::vector<error>>(&m_storage);
  return ptr && !ptr->empty();
}

void result::append_error(error err) {
  if (const auto ptr = std::get_if<std::vector<error>>(&m_storage)) {
    ptr->push_back(std::move(err));
  }
}

const std::vector<error>& result::get_errors() const {
  return std::get<std::vector<error>>(m_storage);
}

}
