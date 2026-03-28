#include <token/range/view.hpp>
#include <token/identifier.hpp>
#include <token/kw_arrow_double.hpp>
#include <token/kw_arrow_down.hpp>
#include <token/kw_arrow_left.hpp>
#include <token/kw_arrow_right.hpp>
#include <token/text.hpp>

#include "operator/all.hpp"
#include "operator/any.hpp"
#include "operator/option.hpp"
#include "operator/result.hpp"
#include "operator/tokened.hpp"
#include "operator/try.hpp"

#include "transition.hpp"

namespace puml::cst {

result transition::try_make(const lex::token_view& tv) {
  return all<transition,
    try_match<tokened<lex::identifier>>,
    try_match<any<
      try_match<tokened<lex::kw_arrow_double>>,
      try_match<tokened<lex::kw_arrow_down>>,
      try_match<tokened<lex::kw_arrow_left>>,
      try_match<tokened<lex::kw_arrow_right>>,
      try_match<tokened<lex::kw_arrow_single>>,
      try_match<tokened<lex::kw_arrow_up>>>>,
    tokened<lex::identifier>,
    option<try_match<tokened<lex::text>>>>::try_make(tv);
}

}
