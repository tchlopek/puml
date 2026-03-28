# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Tomasz Chłopek

CPMAddPackage(
  NAME googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
  URL_HASH SHA256=40d4ec942217dcc84a9ebe2a68584ada7d4a33a8ee958755763278ea1c5e18ff
  VERSION v1.17.0
)

add_executable(pumltest
  parser_test.cpp
  token_test.cpp
  tokenizer_test.cpp
)

target_include_directories(pumltest PRIVATE ${SRC_INCLUDE_DIR})

target_link_libraries(pumltest PRIVATE GTest::gtest GTest::gtest_main gmock_main puml)

message(${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME puml_test_all COMMAND pumltest WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
