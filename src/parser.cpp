// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <puml/puml.hpp>

#include "cst/parser.hpp"
#include "cst/operator/result.hpp"
#include "token/range/range.hpp"
#include "token/result.hpp"
#include "token/tokenizer.hpp"
#include "builder.hpp"
#include "context.hpp"

using namespace puml::lex;

namespace puml {

namespace {

context load_file(const std::filesystem::path& filepath) {
  auto fstream = std::ifstream{ filepath };
  if (!fstream.is_open()) {
    throw std::runtime_error{ "Missing file: " + filepath.string() };
  }

  auto line = std::string{};
  auto lines = std::vector<std::string>{};
  while (std::getline(fstream, line)) {
    lines.push_back(std::move(line));
  }

  return context{ filepath, lines };
}

context load_string(const std::string& string) {
  auto sstream = std::stringstream{ string };
  auto line = std::string{};
  auto lines = std::vector<std::string>{};
  while (std::getline(sstream, line)) {
    lines.push_back(std::move(line));
  }

  return context{ "", lines };
}

std::size_t get_line(const lex::token_view& tv) {
  return tv.begin()->map([](const auto& t){ return t.line(); }) + 1;
}

std::size_t get_column(const lex::token_view& tv) {
  return tv.begin()->map([](const auto& t){ return t.span().first; }) + 1;
}

std::vector<std::string> get_errors(const cst::result& r, const context& ctx) {
  auto vec = std::vector<std::string>{};
  vec.reserve(r.get_errors().size());
  for (const auto& e : r.get_errors()) {
    const auto line = get_line(e.tv);
    const auto column = get_column(e.tv);

    auto msg = ctx.get_filepath().filename().string() +
    ":" + std::to_string(line) +
    ":" + std::to_string(column) +
    ": " + e.message;

    vec.push_back(std::move(msg));
  }
  return vec;
}

}

diagram parse(const std::filesystem::path& filepath) {
  try {
    const auto ctx = load_file(filepath);
    const auto tokens = tokenize(ctx);
    if (!tokens) {
      return diagram{ { tokens.get_error() } };
    }

    auto syntax_tree = cst::parse(token_view{ tokens.get_range() });
    return syntax_tree ?
      build(syntax_tree.unwrap(), ctx) :
      diagram{ get_errors(syntax_tree, ctx) };
  } catch (const std::exception& e) {
    return diagram {
      { "Unable to parse " + filepath.string() + " due to: " + e.what() }
    };
  }
}

diagram parse(const std::string& string) {
  try {
    const auto ctx = load_string(string);
    const auto tokens = tokenize(ctx);
    if (!tokens) {
      return diagram{ { tokens.get_error() } };
    }

    auto syntax_tree = cst::parse(token_view{ tokens.get_range() });
    return syntax_tree ?
      build(syntax_tree.unwrap(), ctx) :
      diagram{ get_errors(syntax_tree, ctx) };
  } catch (const std::exception& e) {
    return diagram {
      { std::string{ "Unable to parse puml due to: " } + e.what() }
    };
  }
}

}
