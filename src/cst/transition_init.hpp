#pragma once

#include <token/range/view_fwd.hpp>

#include "node.hpp"

namespace puml::cst {

class result;
struct transition_init {
  node m_source_id;
  node m_arrow;
  node m_target_id;
  node m_text;

  static result try_make(const token_view& tv);
};

}
