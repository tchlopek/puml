#include <algorithm>
#include <unordered_map>

#include "cst/includes.hpp"
#include "cst/node.hpp"
#include "cst/token.hpp"
#include "context.hpp"
#include "puml/puml.hpp"
#include "puml/state.hpp"
#include "puml/transition.hpp"

#include "builder.hpp"

namespace puml {

namespace {

struct cst_context {
  std::vector<std::string> state_stack;
  std::unordered_map<std::string, std::unique_ptr<::puml::state>> state_map;
  std::vector<::puml::transition> transitions;
  std::vector<::puml::transition> init_transitions;

  diagram make_diagram() {
    auto diagram_states = std::vector<std::unique_ptr<::puml::state>>{};
    diagram_states.reserve(state_map.size());

    for (auto& [_, sdata] : state_map) {
      diagram_states.push_back(std::move(sdata));
    }

    return diagram{
      std::move(diagram_states),
      std::move(transitions),
      std::move(init_transitions)
    };
  }
};


class cst_state_visitor {

public:
  cst_state_visitor(const context& ctx, cst_context& cst_ctx)
    : m_ctx{ ctx }
    , m_cst_ctx{ cst_ctx }
  {}

  void operator()(const box<::puml::cst::block_scope>& block) {
    block->m_node.map(*this);
  }

  void operator()(const box<::puml::cst::list>& list) {
    for (auto& elem : list->m_list) {
      elem.map(*this);
    }
  }

  void operator()(const box<::puml::cst::null>& null) {
  }

  void operator()(const box<::puml::cst::scoped_state>& state) {
    const auto state_name = state->m_name_id.to<::puml::cst::token>().m_tok.str(m_ctx.get_text());

    auto& sdata = m_cst_ctx.state_map[state_name];
    if (!sdata) {
      sdata = std::make_unique<::puml::state>();
      sdata->name = state_name;
    }
    update_parent(sdata.get());
    m_cst_ctx.state_stack.push_back(state_name);
    state->m_scope_block.map(*this);

    m_cst_ctx.state_stack.pop_back();
  }

  void operator()(const box<::puml::cst::simple_state>& state) {
    const auto state_name = state->name_id.to<::puml::cst::token>().m_tok.str(m_ctx.get_text());
    const auto text = to_text(state->annonation);

    auto& ptr = m_cst_ctx.state_map[state_name];
    if (!ptr) {
      ptr = std::make_unique<::puml::state>();
      ptr->name = state_name;
      update_parent(ptr.get());
    }

    ptr->description.push_back(text);
  }

  void operator()(const box<::puml::cst::transition_init>& transition) {
  }

  void operator()(const box<::puml::cst::transition>& transition) {
  }

  void operator()(const box<::puml::cst::token>& token) const {
  }

protected:
  void update_parent(::puml::state* ptr) {
    if (!m_cst_ctx.state_stack.empty()) {
      auto& ancestor = m_cst_ctx.state_map[m_cst_ctx.state_stack.back()];
      const auto is_not_child = std::none_of(
        ancestor->children.begin(),
        ancestor->children.end(),
        [=](const ::puml::state* c){ return c == ptr; });
      if (is_not_child) {
        ancestor->children.push_back(ptr);
        ptr->parent = ancestor.get();
      }
    }
  }

  std::string to_text(const ::puml::cst::node& n) const {
    const auto text = n.to<::puml::cst::token>().m_tok.str(m_ctx.get_text());
    auto index = text.find_first_not_of(':');
    index = text.find_first_not_of(' ', index);
    return text.substr(index, std::string::npos);
  }

  const context& m_ctx;
  cst_context& m_cst_ctx;
};

class cst_transition_visitor : public cst_state_visitor {
public:
  cst_transition_visitor(const context& ctx, cst_context& cst_ctx)
    : cst_state_visitor{ ctx, cst_ctx }
  {}

  void operator()(const box<::puml::cst::block_scope>& block) {
    block->m_node.map(*this);
  }

  void operator()(const box<::puml::cst::list>& list) {
    for (auto& elem : list->m_list) {
      elem.map(*this);
    }
  }

  void operator()(const box<::puml::cst::null>& null) {
  }

  void operator()(const box<::puml::cst::scoped_state>& state) {
    const auto state_name = state->m_name_id.to<::puml::cst::token>().m_tok.str(m_ctx.get_text());
    m_cst_ctx.state_stack.push_back(state_name);
    state->m_scope_block.map(*this);
    m_cst_ctx.state_stack.pop_back();
  }

  void operator()(const box<::puml::cst::simple_state>& state) {
  }

  void operator()(const box<::puml::cst::transition_init>& transition) {
    const auto dst = transition->m_target_id.to<::puml::cst::token>().m_tok.str(m_ctx.get_text());

    auto name = std::string{};
    if (transition->m_text.is<::puml::cst::token>()) {
      name = to_text(transition->m_text);
    }

    const ::puml::state* src_ptr = nullptr;
    if (!m_cst_ctx.state_stack.empty()) {
      src_ptr = m_cst_ctx.state_map[m_cst_ctx.state_stack.back()].get();
    }

    auto& dst_ptr = m_cst_ctx.state_map[dst];
    if (!dst_ptr) {
      dst_ptr = std::make_unique<::puml::state>();
      dst_ptr->name = dst;
      update_parent(dst_ptr.get());
    }

    m_cst_ctx.init_transitions.push_back(::puml::transition{ src_ptr, dst_ptr.get(), name });
  }

  void operator()(const box<::puml::cst::transition>& transition) {
    const auto src = transition->m_source_id.to<::puml::cst::token>().m_tok.str(m_ctx.get_text());
    const auto dst = transition->m_target_id.to<::puml::cst::token>().m_tok.str(m_ctx.get_text());

    auto name = std::string{};
    if (transition->m_text.is<::puml::cst::token>()) {
      name = to_text(transition->m_text);
    }

    auto& src_ptr = m_cst_ctx.state_map[src];
    if (!src_ptr) {
      src_ptr = std::make_unique<::puml::state>();
      src_ptr->name = src;
      update_parent(src_ptr.get());
    }

    auto& dst_ptr = m_cst_ctx.state_map[dst];
    if (!dst_ptr) {
      dst_ptr = std::make_unique<::puml::state>();
      dst_ptr->name = dst;
      update_parent(dst_ptr.get());
    }

    m_cst_ctx.transitions.push_back(::puml::transition{ src_ptr.get(), dst_ptr.get(), name });
  }

  void operator()(const box<::puml::cst::token>& token) const {
  }
};

}

diagram build(cst::node root, const context& ctx) {
  auto cst_ctx = cst_context{};

  {
    auto visitor = cst_state_visitor{ ctx, cst_ctx };
    root.map(visitor);
  }

  {
    auto visitor = cst_transition_visitor{ ctx, cst_ctx };
    root.map(visitor);
  }

  return cst_ctx.make_diagram();
}

}

