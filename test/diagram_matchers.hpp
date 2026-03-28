#pragma once

#include <gmock/gmock.h>
#include <puml/puml.hpp>
#include <algorithm>

// Matcher to check if diagram has a state with the given name
MATCHER_P(HasStateWithName, expected_name, "") {
  const auto& states = arg.get_states();
  return std::any_of(states.begin(), states.end(),
                     [this](const std::unique_ptr<puml::state>& s) {
                       return s->name == this->expected_name;
                     });
}

// Matcher to check if diagram has no errors
MATCHER(HasNoErrors, "") {
  return arg.get_errors().empty();
}

// Matcher to check if diagram has a specific number of states
MATCHER_P(HasStateCount, expected_count, "") {
  return arg.get_states().size() == static_cast<size_t>(expected_count);
}

// Matcher to check if diagram is valid (no errors)
MATCHER(IsValid, "") {
  return static_cast<bool>(arg);
}

// Matcher to check if diagram has a transition from source to target with optional text
MATCHER_P3(HasTransition, source_name, target_name, text, "") {
  const auto& transitions = arg.get_transition();
  const auto& states = arg.get_states();
  const puml::state* source = nullptr;
  const puml::state* target = nullptr;

  for (const auto& s : states) {
    if (s->name == source_name) source = s.get();
    if (s->name == target_name) target = s.get();
  }

  if (!source || !target) return false;

  return std::any_of(transitions.begin(), transitions.end(),
                     [this, source, target](const puml::transition& t) {
                       return t.source == source && t.target == target && t.text == this->text;
                     });
}

// Matcher to check if diagram has a transition from source to target (any text)
MATCHER_P2(HasTransitionBetween, source_name, target_name, "") {
  const auto& transitions = arg.get_transition();
  const auto& states = arg.get_states();
  const puml::state* source = nullptr;
  const puml::state* target = nullptr;

  for (const auto& s : states) {
    if (s->name == source_name) source = s.get();
    if (s->name == target_name) target = s.get();
  }

  if (!source || !target) return false;

  return std::any_of(transitions.begin(), transitions.end(),
                     [source, target](const puml::transition& t) {
                       return t.source == source && t.target == target;
                     });
}

// Matcher to check if diagram has an initial transition
MATCHER_P(HasInitialTransitionTo, target_name, "") {
  const auto& init_transitions = arg.get_init_transitions();
  const auto& states = arg.get_states();
  const puml::state* target = nullptr;

  for (const auto& s : states) {
    if (s->name == target_name) target = s.get();
  }

  if (!target) return false;

  return std::any_of(init_transitions.begin(), init_transitions.end(),
                     [&](const puml::transition& t) {
                       return t.target == target;
                     });
}