#pragma once

#include <string>
#include <vector>

namespace tkn {
class range;
}

tkn::range tokenize(const std::vector<std::string>& text);
