# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Tomasz Chłopek

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

target_include_directories(puml
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
)

add_subdirectory(cst)
add_subdirectory(token)

target_sources(puml PRIVATE
  builder.cpp
  context.cpp
  diagram.cpp
  parser.cpp
)

install(TARGETS puml
  EXPORT pumlTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${INCLUDE_DIR}/puml DESTINATION include)

install(EXPORT pumlTargets
  FILE pumlTargets.cmake
  NAMESPACE puml::
  DESTINATION lib/cmake/puml
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/pumlConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/pumlConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/puml"
  NO_SET_AND_CHECK_MACRO
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/pumlConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/pumlConfigVersion.cmake"
  DESTINATION lib/cmake/puml
)

