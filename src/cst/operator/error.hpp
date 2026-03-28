#pragma once

#include <string>

#include <token/range/view.hpp>

namespace puml::cst {

struct error {
  std::string message;
  token_view tv;
};

}
