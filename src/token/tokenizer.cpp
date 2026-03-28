#include <optional>
#include <vector>

#include "range/range.hpp"
#include "token/result.hpp"
#include "tokenizer.hpp"

namespace puml::lex {

namespace {

template<typename token_t, typename... token_ts>
std::optional<puml::lex::token>
match_token(const std::string& str, std::size_t line, std::size_t pos) {
  if (const auto token = token_t::try_make(str, line, pos)) {
    return puml::lex::token{ *token };
  } else {
    if constexpr (sizeof...(token_ts) > 0) {
      return match_token<token_ts...>(str, line, pos);
    } else {
      return std::nullopt;
    }
  }
}

template<typename>
struct make_token;

template<typename... token_ts>
struct make_token<std::variant<token_ts...>> {
  std::optional<puml::lex::token>
  operator()(const std::string& str, std::size_t line, std::size_t pos) const {
    return match_token<token_ts...>(str, line, pos);
  }
};

}

result tokenize(const puml::context& ctx) {
  std::vector<token> tokens;
  const make_token<token::type> token_creator;
  for (std::size_t lineno = 0; lineno != ctx.get_text().size(); ++lineno) {
    for (std::size_t pos = 0; pos != ctx.get_line(lineno).length();) {
      if (const auto token = token_creator(ctx.get_line(lineno), lineno, pos)) {
        tokens.push_back(*token);
        // advance to end position (span returns start,end)
        pos = token->map([](const auto& t) { return t.span().second; });
      } else if (ctx.get_line(lineno)[pos] != ' ') {
        return result{
          "Unexpected token at line " +
          std::to_string(lineno) +
          " position " +
          std::to_string(pos)
        };
      } else {
        ++pos;
      }
    }
  }
  return result{ std::move(tokens) };
}

}
