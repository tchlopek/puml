#include <token/range/view.hpp>

#include "operator/any.hpp"
#include "operator/result.hpp"

#include "scoped_state.hpp"
#include "simple_state.hpp"
#include "stmt.hpp"
#include "transition_init.hpp"
#include "transition.hpp"
#include "types.hpp"

namespace puml::cst {

result stmt::try_make(const token_view& tv) {
  auto r = any<
    scoped_state,
    simple_state,
    transition_init,
    transition,
    block_stmt_quiet>::try_make(tv);

  if (!r && !r.is_fatal()) {
    return error{ "invalid syntax", tv };
  }

  return r;
}

}