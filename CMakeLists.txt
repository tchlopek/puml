# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Tomasz Chłopek

cmake_minimum_required(VERSION 3.13)
project(parser
  VERSION 0.1.0
  DESCRIPTION "X lang parser"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TEST "Enables unit-test build" OFF)

set(CPM_DOWNLOAD_VERSION 0.42.0)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  message(STATUS "Downloading CPM.cmake")
  file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)

if (BUILD_TEST)
  enable_testing()
  add_subdirectory(test)
endif()
