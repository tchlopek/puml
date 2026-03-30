# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Tomasz Chłopek

cmake_minimum_required(VERSION 3.13)
project(puml-parser
  VERSION 0.2.1
  DESCRIPTION "PlantUML state diagram parser"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TEST "Enables unit-test build" OFF)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)

if (BUILD_TEST)
  enable_testing()
  add_subdirectory(test)
endif()
