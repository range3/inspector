#pragma once

#include <ostream>
#include <sstream>
#include <type_traits>

namespace insp {

template <typename T>
struct inspector {
  static auto inspect(std::ostream& os, const T& obj) -> std::ostream& {
    return os << obj;
  }
};

namespace detail {

template <typename T, typename = void, typename = void>
constexpr bool has_inspect_member = false;

template <typename T>
constexpr bool has_inspect_member<
    T,
    std::void_t<decltype(std::declval<T&>().inspect(
        std::declval<std::ostream&>()))>,
    std::enable_if_t<std::is_same_v<std::ostream&,
                                    decltype(std::declval<T&>().inspect(
                                        std::declval<std::ostream&>()))>>> =
    true;

template <typename T, typename = void, typename = void>
constexpr bool has_adl_inspect = false;

template <typename T>
constexpr bool has_adl_inspect<
    T,
    std::void_t<decltype(inspect(std::declval<std::ostream&>(),
                                 std::declval<const T&>()))>,
    std::enable_if_t<
        std::is_same_v<std::ostream&,
                       decltype(inspect(std::declval<std::ostream&>(),
                                        std::declval<const T&>()))>>> = true;

template <typename T>
struct inspectee_wrapper {
  const T* obj;
  explicit inspectee_wrapper(const T& object) : obj(&object) {}
};

template <typename T>
auto operator<<(std::ostream& os,
                const inspectee_wrapper<T>& insp) -> std::ostream& {
  if constexpr (has_inspect_member<T>) {
    return insp.obj->inspect(os);
  } else if constexpr (has_adl_inspect<T>) {
    return inspect(os, *insp.obj);
  } else {
    return inspector<T>::inspect(os, *insp.obj);
  }
}

}  // namespace detail

template <typename T>
auto make_inspectable(const T& obj) -> detail::inspectee_wrapper<T> {
  return detail::inspectee_wrapper<T>(obj);
}

template <typename T>
auto to_string(const T& obj) -> std::string {
  std::stringstream ss;
  ss << make_inspectable(obj);
  return ss.str();
}

}  // namespace insp
