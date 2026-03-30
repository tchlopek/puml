// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#include <puml/puml.hpp>

namespace puml {

struct diagram::_diagram {
  std::vector<std::unique_ptr<state>> states;
  std::vector<transition> transitions;
  std::vector<transition> init_transitions;
  std::vector<std::string> errors;
  std::string title;
};

void diagram::_diagram_deleter::operator()(_diagram* ptr) const {
  std::default_delete<_diagram>{}(ptr);
}

diagram::diagram()
  : m_pimpl{ std::unique_ptr<_diagram, _diagram_deleter>{ new _diagram{} } }
{}

diagram::diagram(std::vector<std::string>&& errors)
  : diagram()
{
  m_pimpl->errors = std::move(errors);
}

diagram::diagram(
  std::vector<std::unique_ptr<state>>&& states,
  std::vector<transition>&& transitions,
  std::vector<transition>&& init_transitions,
  std::string&& title
) : diagram() 
{
  m_pimpl->states = std::move(states);
  m_pimpl->transitions = std::move(transitions);
  m_pimpl->init_transitions = std::move(init_transitions);
  m_pimpl->title = std::move(title);
}

diagram::operator bool() const {
  return m_pimpl->errors.empty();
}

const std::vector<std::unique_ptr<state>>& diagram::get_states() const {
  return m_pimpl->states;
}

const std::vector<transition>& diagram::get_transition() const {
  return m_pimpl->transitions;
}

const std::vector<transition>& diagram::get_init_transitions() const {
  return m_pimpl->init_transitions;
}

const std::vector<std::string>& diagram::get_errors() const {
  return m_pimpl->errors;
}

const std::string& diagram::get_title() const {
  return m_pimpl->title;
}

}
