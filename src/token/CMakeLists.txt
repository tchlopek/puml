# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Tomasz Chłopek

add_subdirectory(range)

target_sources(puml PRIVATE
  result.cpp
  tokenizer.cpp
)
