#pragma once

#include <context.hpp>

namespace puml::lex {

class result;

result tokenize(const puml::context& ctx);

}
