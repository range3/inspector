#pragma once

#include <optional>
#include <ostream>

#include "core.hpp"

namespace inspector {

template <typename T>
struct inspector<std::optional<T>> {
  static auto inspect(std::ostream& os,
                      const std::optional<T>& obj) -> std::ostream& {
    if (obj) {
      return os << make_inspectable(*obj);
    }
    return os << "nullopt";
  }
};

}  // namespace inspector
