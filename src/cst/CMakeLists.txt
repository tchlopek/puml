target_sources(puml PRIVATE
  node.cpp
  parser.cpp
  scoped_state.cpp
  simple_state.cpp
  stmt.cpp
  title.cpp
  transition_init.cpp
  transition.cpp
)

# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Tomasz Chłopek

add_subdirectory(operator)
