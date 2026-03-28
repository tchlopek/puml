#pragma once

#include <token/token.hpp>

#include "operator/bracketed.hpp"
#include "operator/sequenced.hpp"
#include "operator/tokened.hpp"
#include "operator/try.hpp"
#include "block_scope.hpp"
#include "stmt.hpp"

namespace puml::cst {

template<bool early_error>
using block_stmt_impl = bracketed<
  block_scope,
  lex::l_brace,
  sequenced<stmt>, early_error>;

using block_stmt = block_stmt_impl<true>;
using block_stmt_quiet = block_stmt_impl<false>;

using startuml_stmt = try_match<tokened<lex::kw_startuml>>;
using enduml_stmt = try_match<tokened<lex::kw_enduml>>;

}
