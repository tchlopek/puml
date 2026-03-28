#pragma once

#include <variant>

#include <common/box.hpp>

namespace puml::cst {

struct block_scope;
struct list;
struct null;
struct scoped_state;
struct simple_state;
struct transition_init;
struct transition;
struct token;

class node {
  using storage_t = std::variant<
    box<block_scope>,
    box<list>,
    box<null>,
    box<scoped_state>,
    box<simple_state>,
    box<transition_init>,
    box<transition>,
    box<token>>;

public:
  explicit node(storage_t, std::size_t);

  template<typename fn_t>
  decltype(auto) map(fn_t&& fn) const {
    return std::visit(std::forward<fn_t>(fn), m_storage);
  }

  template<typename node_t>
  const node_t& to() const {
    return *std::get<box<node_t>>(m_storage);
  }

  template<typename... token_ts>
  bool is() const {
    return (std::holds_alternative<box<token_ts>>(m_storage) || ...);
  }

  std::size_t get_len() const;

private:
  storage_t m_storage;
  std::size_t m_len;
};

}
