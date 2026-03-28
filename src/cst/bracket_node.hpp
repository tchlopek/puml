#pragma once

#include <token/token.hpp>

#include "node.hpp"

namespace puml::cst {

struct bracket_node {
  puml::token m_lb;
  puml::token m_rb;
  node m_node;
};

}