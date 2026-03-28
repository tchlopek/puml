#pragma once

#include <vector>

#include "node.hpp"

namespace puml::cst {

struct list {
  std::vector<node> m_list;
};

}