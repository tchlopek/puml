add_library(puml)

if (BUILD_SHARED_LIBS)
  target_compile_definitions(puml PRIVATE PUML_SHARED_BUILD)
else()
  target_compile_definitions(puml PUBLIC PUML_STATIC_BUILD)
endif()

set_target_properties(puml
  PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

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
