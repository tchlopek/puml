// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <filesystem>
#include <memory>
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
    std::vector<transition>&& init_transitions,
    std::string&& title);

  operator bool() const;

  const std::vector<std::unique_ptr<state>>& get_states() const;
  const std::vector<transition>& get_transition() const;
  const std::vector<transition>& get_init_transitions() const;
  const std::vector<std::string>& get_errors() const;
  const std::string& get_title() const;

private:
  diagram();

  struct _diagram;
  struct _diagram_deleter{ void operator()(_diagram*) const; };
  std::unique_ptr<_diagram, _diagram_deleter> m_pimpl;
};

PUML_API diagram parse(const std::filesystem::path& filepath);
PUML_API diagram parse(const std::string& string);

}
