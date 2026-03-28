#pragma once

#include <vector>
#include <string>

#include <puml/puml.hpp>

#include "cst/node.hpp"

#include "context.hpp"

namespace puml {

diagram build(cst::node r, const context& ctx);

}

