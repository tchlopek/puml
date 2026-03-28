target_sources(puml PRIVATE
  node.cpp
  parser.cpp
  scoped_state.cpp
  simple_state.cpp
  stmt.cpp
  transition_init.cpp
  transition.cpp
)

add_subdirectory(operator)
