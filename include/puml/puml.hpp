// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "state.hpp"
#include "transition.hpp"
#include "api.hpp"

namespace puml {

class PUML_API diagram {
public:
  explicit diagram(std::vector<std::string>&& errors);

  diagram(
    std::vector<std::unique_ptr<state>>&& states,
    std::vector<transition>&& transitions,
    std::vector<transition>&& init_transitions);

  operator bool() const;

  const std::vector<std::unique_ptr<state>>& get_states() const;
  const std::vector<transition>& get_transition() const;
  const std::vector<transition>& get_init_transitions() const;
  const std::vector<std::string>& get_errors() const;

private:
  std::vector<std::unique_ptr<state>> m_states;
  std::vector<transition> m_transitions;
  std::vector<transition> m_init_transitions;
  std::vector<std::string> m_errors;
};

PUML_API diagram parse(const std::filesystem::path& filepath);
PUML_API diagram parse(const std::string& string);

}
