#pragma once

#include <context.hpp>

namespace puml::lex {

class token_range;

token_range tokenize(const puml::context& ctx);

}
