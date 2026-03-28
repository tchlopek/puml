#pragma once

#include <string>
#include <vector>

namespace puml {

struct state {
  std::string name;
  std::vector<std::string> description;
  std::vector<const state*> children;
  const state* parent;
};

}
