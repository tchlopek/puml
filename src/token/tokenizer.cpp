#include <optional>
#include <vector>

#include <token/range/range.hpp>
#include <token/tokenizer.hpp>

namespace {
template<typename token_t, typename... token_ts>
std::optional<tkn::token>
match_token(const std::string& str, std::size_t line, std::size_t pos) {
  if (const auto token = token_t::try_make(str, line, pos)) {
    return tkn::token{ *token };
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
  std::optional<tkn::token>
  operator()(const std::string& str, std::size_t line, std::size_t pos) const {
    return match_token<token_ts...>(str, line, pos);
  }
};
}    // namespace

tkn::range tokenize(const std::vector<std::string>& text) {
  std::vector<tkn::token> tokens;
  const make_token<tkn::token::type> token_creator;
  for (std::size_t line = 0; line != text.size(); ++line) {
    for (std::size_t pos = 0; pos != text[line].length();) {
      if (const auto token = token_creator(text[line], line, pos)) {
        tokens.push_back(*token);
        // advance to end position (span returns start,end)
        pos = token->map([](const auto& t) { return t.span().second; });
      } else {
        ++pos;
      }
    }
  }
  return { std::move(tokens) };
}
