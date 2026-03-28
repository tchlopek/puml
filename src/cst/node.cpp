// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#include "includes.hpp"
#include "node.hpp"

namespace puml::cst {

node::node(storage_t storage, std::size_t len)
  : m_storage{ std::move(storage) }
  , m_len{ len }
{}

std::size_t node::get_len() const {
  return m_len;
}

}
