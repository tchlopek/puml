#include <token/range/view.hpp>
#include <token/identifier.hpp>
#include <token/text.hpp>

#include "operator/all.hpp"
#include "operator/result.hpp"
#include "operator/tokened.hpp"
#include "operator/try.hpp"

#include "simple_state.hpp"

namespace puml::cst {

result simple_state::try_make(const token_view& tv) {
  return all<simple_state,
    try_match<tokened<identifier>>,
    try_match<tokened<text>>>::try_make(tv);
}

}
