#pragma once

#include <variant>
#include <vector>

#include <cst/includes.hpp>
#include <cst/node.hpp>

#include "error.hpp"

namespace puml::cst {

class result {
public:
  result();
  result(error err);
  result(node&& node);

  explicit operator bool() const;
  const node* operator->() const;
  node&& unwrap();
  bool is_fatal() const;
  void append_error(error err);
  const std::vector<error>& get_errors() const;

private:
  std::variant<node, std::vector<error>> m_storage;
};

}
