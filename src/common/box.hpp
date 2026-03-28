// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#pragma once

#include <memory>

namespace puml {

template<typename T>
class box : private std::unique_ptr<T> {
  using base_t = std::unique_ptr<T>;

  template<typename U>
  friend class box;

public:
  using typename base_t::unique_ptr;

  box(std::nullptr_t) = delete;
  box() = delete;
  explicit box(T&& val)
    : base_t{ new T(std::move(val)) } {
  }

  template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
  box(box<U>&& u) noexcept
    : base_t{ std::move(u) } {
  }

  explicit box(const T& val)
    : base_t{ new T(val) } {
  }

  const T* operator->() const noexcept {
    return base_t::operator->();
  }

  T* operator->() noexcept {
    return base_t::operator->();
  }

  const T& operator*() const noexcept {
    return base_t::operator*();
  }
};

}
