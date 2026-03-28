#include <token/range/view.hpp>
#include <token/identifier.hpp>
#include <token/kw_state.hpp>

#include "operator/all.hpp"
#include "operator/result.hpp"
#include "operator/tokened.hpp"
#include "operator/try.hpp"

#include "scoped_state.hpp"
#include "types.hpp"

namespace puml::cst {

result scoped_state::try_make(const lex::token_view& tv) {
  return all<scoped_state,
    try_match<tokened<lex::kw_state>>,
    tokened<lex::identifier>,
    block_stmt>::try_make(tv);
}

}
