#pragma once

#include <cstdlib>
#include <vector>

#include <common/box.hpp>
#include <cst/includes.hpp>
#include <cst/list.hpp>
#include <cst/node.hpp>
#include <token/is_token.hpp>
#include <token/range/view.hpp>

#include "result.hpp"

namespace puml::cst {

template<typename node_t>
class sequenced {
public:
  static result try_make(const token_view& tv) {
    if (tv.size() == 0) {
      return node{ box{ list{ std::vector<node>{} } }, 0 };
    }

    auto start = tv.span().first;
    std::vector<node> seq;
    do {
      auto n = node_t::try_make(tv.slice_left(start));
      if (!n) {
        return n;
      }

      start += n->get_len();
      seq.push_back(n.unwrap());
    } while (start != tv.span().second);

    return node{ box{ list{ std::move(seq) } }, tv.size() };
  }
};

template<typename node_t, typename sep_t, std::size_t at_least = 0>
class sequenced_sep {
public:
  static result try_make(const token_view& tv) {
    if (tv.size() == 0) {
      return node{ box{ list{ std::vector<node>{} } }, 0 };
    }
    auto tview = tv;
    std::vector<node> seq;
    while (auto sep = tview.find_global_left(is_token<sep_t>{})) {
      if (auto n = node_t::try_make(tview.slice_right(sep->index()))) {
        seq.push_back(n.unwrap());
        tview = tview.slice_left(sep->index() + 1);
      } else {
        n.append_error(error{
          "invalid syntax in the sequence before: '"
          + std::string{ sep_t::name }
          + "'", tv.slice_left(sep->index()) });
        return n;
      }
    }

    if (tview.size() != 0) {
      if (auto n = node_t::try_make(tview)) {
        seq.push_back(n.unwrap());
      } else {
        n.append_error(error{
          "invalid syntax in the sequence after: '"
          + std::string{ sep_t::name }
          + "'", tview });
        return n;
      }
    }

    if (seq.size() < at_least) {
      return result{ error{
        "expected at least "
        + std::to_string(at_least)
        + " elements in the sequence, while it has "
        + std::to_string(seq.size()), tv } };
    }

    return !seq.empty()
           ? node{ box{ list{ std::move(seq) } }, tv.size() }
           : result{};
  }
};

}
