#include <token/range/view.hpp>

#include "operator/sequenced.hpp"
#include "stmt.hpp"

#include "parser.hpp"

namespace puml::cst {

namespace {

std::string to_string(const std::vector<std::string>& text, std::size_t line) {
  return text[line];
}

std::size_t get_line(const token_view& tv) {
  return tv.begin()->map([](const auto& t){ return t.line(); }) + 1;
}

std::size_t get_column(const token_view& tv) {
  return tv.begin()->map([](const auto& t){ return t.span().first; }) + 1;
}

}

result parse(const token_view& tokens) {
  auto res = sequenced<stmt>::try_make(tokens);
  return res;
}

}
