#pragma once

#include <token/token.hpp>

#include "node.hpp"

namespace puml::cst {

struct bracket_node {
  puml::lex::token m_lb;
  puml::lex::token m_rb;
  node m_node;
};

}