// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <puml/puml.hpp>

#include "cst/node.hpp"

#include "context.hpp"

namespace puml {

diagram build(cst::node r, const context& ctx);

}

