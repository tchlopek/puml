#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <interp/exec.hpp>
#include <parser/ast/includes.hpp>
#include <parser/ast/serializer.hpp>
#include <parser/parser.hpp>
#include <token/range/range.hpp>
#include <token/range/view.hpp>
#include <token/token.hpp>
#include <token/tokenizer.hpp>

std::vector<std::string> get_text(const std::filesystem::path& file) {
  std::vector<std::string> text;
  if (std::ifstream ifile{ file }) {
    for (std::string line; std::getline(ifile, line);) {
      text.push_back(std::move(line));
    }
  }
  return text;
}

int main(const int argc, const char* const* argv) {
  if (argc != 3) {
    std::cerr << "invalid arguments\n";
    return -1;
  }

  const auto text = get_text(
    std::filesystem::current_path() / "example" / argv[2]
  );
  if (text.empty()) {
    std::cerr << "empty file\n";
    return -1;
  }

  const auto tokens = tokenize(text);

  try {
    if (const auto ast = parser::parse(tkn::view{ tokens }, text)) {
      if (std::string_view{ argv[1] } == "-ast") {
        std::cout << parser::ast::serialize(*ast, text);
      } else if (std::string_view{ argv[1] } == "-exec") {
        std::cout << interp::exec(*ast, text) << std::endl;
      } else {
        std::cerr << "invalid option\n";
        return -1;
      }
    } else {
      std::cout << "parse error\n";
    }
  } catch (const std::runtime_error& err) {
    std::cout << "Exception: " << err.what() << std::endl;
  }

  return 0;
}
