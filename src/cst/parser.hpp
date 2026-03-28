#pragma once

#include <token/range/view.hpp>

#include "operator/result.hpp"

namespace puml::cst {

result parse(const lex::token_view& tokens);

}
