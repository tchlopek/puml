// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <context.hpp>

namespace puml::lex {

class result;

result tokenize(const puml::context& ctx);

}
