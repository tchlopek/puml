#pragma once

#include <tuple>

#include <token/range/view.hpp>

#include "result.hpp"

namespace puml::cst {

namespace detail {

template<typename... Ts>
auto all_failed() {
  return std::tuple{ (void(std::is_same_v<Ts, int>), result{})... };
}

template<typename T, typename... Ts>
auto all(const lex::token_view& tv) {
  auto node = T::try_make(tv);
  if (!node) {
    return std::tuple_cat(std::tuple{ std::move(node) }, all_failed<Ts...>());
  }

  if constexpr (sizeof...(Ts) > 0) {
    const auto next = tv.slice_left(tv.span().first + node->get_len());
    return std::tuple_cat(std::tuple{ std::move(node) }, all<Ts...>(next));
  } else {
    return std::tuple{ std::move(node) };
  }
}

template<std::size_t I, typename... Ts>
result* get_failed(std::tuple<Ts...>& args) {
  if constexpr (I < sizeof...(Ts)) {
    if (!std::get<I>(args)) {
      return &std::get<I>(args);
    }
    return get_failed<I + 1>(args);
  } else {
    return nullptr;
  }
}

template<typename... results>
result* get_failed(std::tuple<results...>& res) {
  return detail::get_failed<0>(res);
}

template<typename... results>
std::size_t get_len(const std::tuple<results...>& res) {
  return std::apply([](auto&... res) { return (res->get_len() + ...); }, res);
}

}

template<typename node_t, typename... Ts>
struct all {
  static result try_make(const lex::token_view& tv) {
    auto nodes = detail::all<Ts...>(tv);
    if (auto* const failed = detail::get_failed(nodes)) {
      return std::move(*failed);
    }

    const auto unwrap = [](auto&... res) { return node_t{ res.unwrap()... }; };
    return node{ box{ std::apply(unwrap, nodes) }, detail::get_len(nodes) };
  }
};

}
