#pragma once

#include <token/token.hpp>

#include "operator/bracketed.hpp"
#include "operator/sequenced.hpp"
#include "block_scope.hpp"
#include "stmt.hpp"

namespace puml::cst {

template<bool early_error>
using block_stmt_impl = bracketed<block_scope, l_brace, sequenced<stmt>, early_error>;
using block_stmt = block_stmt_impl<true>;
using block_stmt_quiet = block_stmt_impl<false>;

}
