#pragma once

#include <token/is_token.hpp>

#include "view.hpp"

namespace tkn {
template<typename... token_ts>
bool search(const view& tview) noexcept {
  auto first = tview.span().first;
  return (tview.get_if(first++, is_token<token_ts>{}).has_value() && ...);
}

template<typename... token_ts>
bool search_right(const view& tview) noexcept {
  auto last = tview.span().second - sizeof...(token_ts);
  return (tview.get_if(last++, is_token<token_ts>{}).has_value() && ...);
}
}    // namespace tkn
