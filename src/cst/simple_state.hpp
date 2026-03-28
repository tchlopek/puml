#pragma once

#include <token/range/view_fwd.hpp>

#include "node.hpp"

namespace puml::cst {

class result;
struct simple_state {
  node name_id;
  node annonation;

  static result try_make(const lex::token_view& tv);
};

}