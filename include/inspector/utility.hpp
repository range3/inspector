#pragma once

#include <ostream>
#include <tuple>
#include <utility>

#include "core.hpp"

namespace insp {

template <typename T1, typename T2>
struct inspector<std::pair<T1, T2>> {
  static auto inspect(std::ostream& os,
                      const std::pair<T1, T2>& obj) -> std::ostream& {
    return os << '(' << make_inspectable(obj.first) << ", "
              << make_inspectable(obj.second) << ')';
  }
};

namespace detail {

template <typename Tuple, std::size_t... I>
auto tuple_inspect_impl(std::ostream& os,
                        const Tuple& obj,
                        std::index_sequence<I...> /*unused*/) -> std::ostream& {
  os << '(';
  if constexpr (sizeof...(I) > 0) {
    ((os << (I == 0 ? "" : ", ") << make_inspectable(std::get<I>(obj))), ...);
  }
  return os << ')';
}

}  // namespace detail

template <typename... Args>
struct inspector<std::tuple<Args...>> {
  static auto inspect(std::ostream& os,
                      const std::tuple<Args...>& obj) -> std::ostream& {
    return detail::tuple_inspect_impl(
        os, obj, std::make_index_sequence<sizeof...(Args)>{});
  }
};

}  // namespace insp
