#pragma once

#include <puml/puml.hpp>

#include "cst/node.hpp"

#include "context.hpp"

namespace puml {

diagram build(cst::node r, const context& ctx);

}

