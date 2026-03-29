// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#include <puml/puml.hpp>

namespace puml {

diagram::diagram(std::vector<std::string>&& errors)
  : m_errors{ std::move(errors) }
{}

diagram::diagram(
  std::vector<std::unique_ptr<state>>&& states,
  std::vector<transition>&& transitions,
  std::vector<transition>&& init_transitions,
  std::string&& title
) : m_states{ std::move(states) }
  , m_transitions{ std::move(transitions) }
  , m_init_transitions{ std::move(init_transitions) }
  , m_title{ std::move(title) }
{}

diagram::operator bool() const {
  return m_errors.empty();
}

const std::vector<std::unique_ptr<state>>& diagram::get_states() const {
  return m_states;
}

const std::vector<transition>& diagram::get_transition() const {
  return m_transitions;
}

const std::vector<transition>& diagram::get_init_transitions() const {
  return m_init_transitions;
}

const std::vector<std::string>& diagram::get_errors() const {
  return m_errors;
}

const std::string& diagram::get_title() const {
  return m_title;
}

}
