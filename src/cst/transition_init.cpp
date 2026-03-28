#include <token/range/view.hpp>
#include <token/identifier.hpp>
#include <token/kw_arrow_double.hpp>
#include <token/kw_arrow_down.hpp>
#include <token/kw_arrow_left.hpp>
#include <token/kw_arrow_right.hpp>
#include <token/kw_star.hpp>
#include <token/text.hpp>

#include "operator/all.hpp"
#include "operator/any.hpp"
#include "operator/option.hpp"
#include "operator/result.hpp"
#include "operator/tokened.hpp"
#include "operator/try.hpp"

#include "transition_init.hpp"

namespace puml::cst {

result transition_init::try_make(const token_view& tv) {
  return all<transition_init,
    try_match<tokened<kw_star>>,
    any<
      try_match<tokened<kw_arrow_double>>,
      try_match<tokened<kw_arrow_down>>,
      try_match<tokened<kw_arrow_left>>,
      try_match<tokened<kw_arrow_right>>,
      try_match<tokened<kw_arrow_single>>,
      try_match<tokened<kw_arrow_up>>>,
    tokened<identifier>,
    option<try_match<tokened<text>>>>::try_make(tv);
}

}
