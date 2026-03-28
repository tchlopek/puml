add_library(puml)

target_include_directories(puml PUBLIC ${INCLUDE_DIR})
target_include_directories(puml PRIVATE ${SRC_INCLUDE_DIR})

add_subdirectory(cst)
add_subdirectory(token)

target_sources(puml PRIVATE
  builder.cpp
  context.cpp
  diagram.cpp
  parser.cpp
)