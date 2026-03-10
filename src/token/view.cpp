#include <stack>

#include <token/is_token.hpp>
#include <token/range/element.hpp>
#include <token/range/range.hpp>
#include <token/range/view.hpp>

namespace tkn {
namespace {
template<typename lhs, typename rhs>
std::optional<element> find_closing_bracket(const view& tv, const element& elem) {
  auto paren_view = tv.slice_left(elem.index());
  std::stack<element> tq;

  while (const auto p = paren_view.find_any_left(is_token<lhs, rhs>{})) {
    if (p->get().template is<lhs>()) {
      tq.push(*p);
    } else if (tq.pop(); tq.empty()) {
      return p;
    }
    paren_view = paren_view.slice_left(p->index() + 1);
  }

  return {};
}

bool is_between_brackets(const view& tv, const element& te) {
  auto tvtmp = tv;
  const auto get_left = [&] {
    return tvtmp.find_any_left(is_token<l_brace>{});
  };
  for (auto l = get_left(); l && l->index() < te.index(); l = get_left()) {
    if (const auto r = tvtmp.find_closing_bracket(*l)) {
      if (r->index() > te.index()) {
        return true;
      }
      tvtmp = tvtmp.slice_left(r->index());
    } else {
      break;
    }
  }
  return false;
}

template<typename fn_t>
std::optional<element> find_global(const view& tv, const fn_t& fn) {
  auto view = tv;
  while (const auto elem = fn(view)) {
    if (!is_between_brackets(tv, *elem)) {
      return elem;
    }
    view = view.slice_right(elem->index());
  }
  return {};
}
}    // namespace

view::view(const range& rng)
  : view{ &rng, 0, rng.size() } {
}

view::view(const range* rng, std::size_t first, std::size_t last)
  : range_ptr{ rng }
  , first{ first }
  , last{ last } {
}

std::optional<tkn::token> view::get_if(std::size_t index, const pred_t& pred)
  const {
  if (!in_range(index)) {
    return {};
  }

  const auto iter = range_ptr->begin() + index;
  return pred(*iter) ? std::optional{ *iter } : std::nullopt;
}

std::optional<element> view::find_any_left(const view::pred_t& pred) const {
  const auto iter = std::find_if(
    range_ptr->begin() + first,
    range_ptr->begin() + last,
    pred
  );
  const std::size_t index = std::distance(range_ptr->begin(), iter);
  return in_range(index) ? std::optional{ element{ *iter, index } }
                         : std::nullopt;
}

std::optional<element> view::find_any_right(const view::pred_t& pred) const {
  std::reverse_iterator b{ range_ptr->begin() + last };
  std::reverse_iterator e{ range_ptr->begin() + first };

  const auto iter = std::find_if(b, e, pred);
  const std::size_t index = std::distance(range_ptr->begin(), iter.base()) - 1;
  return in_range(index) ? std::optional{ element{ *iter, index } }
                         : std::nullopt;
}

std::optional<element> view::find_global_left(const view::pred_t& pred) const {
  return find_global(*this, [&](const view& tv) {
    return tv.find_any_left(pred);
  });
}

std::optional<element> view::find_global_right(const view::pred_t& pred) const {
  return find_global(*this, [&](const view& tv) {
    return tv.find_any_right(pred);
  });
}

std::optional<element> view::find_closing_bracket(const element& elem) const {
  if (elem.get().is<l_brace>()) {
    return ::tkn::find_closing_bracket<l_brace, r_brace>(*this, elem);
  } else {
    return {};
  }
}

std::pair<std::size_t, std::size_t> view::span() const {
  return { first, last };
}

view view::slice(std::size_t b, std::size_t e) const {
  b = std::clamp(b, first, last);
  e = std::clamp(e, first, last);
  return view{ range_ptr, std::min(b, e), std::max(b, e) };
}

view view::slice_left(std::size_t f) const {
  return slice(f, last);
}

view view::slice_right(std::size_t e) const {
  return slice(first, e);
}

std::size_t view::size() const {
  return last - first;
}

view::iterator view::begin() const {
  return range_ptr->begin() + first;
}

view::iterator view::end() const {
  return range_ptr->begin() + last;
}

bool view::in_range(std::size_t index) const {
  return index >= first && index < last;
}
}    // namespace tkn
