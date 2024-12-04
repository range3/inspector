#pragma once

#include <chrono>
#include <ratio>
#include <string_view>

#include "core.hpp"

namespace insp {
namespace detail {

struct duration_unit {
  static constexpr auto year = "y";
  static constexpr auto month = "mo";
  static constexpr auto week = "w";
  static constexpr auto day = "d";
  static constexpr auto hour = "h";
  static constexpr auto minute = "min";
  static constexpr auto second = "s";
  static constexpr auto millisecond = "ms";
  static constexpr auto microsecond = "us";
  static constexpr auto nanosecond = "ns";
  static constexpr auto unknown = "unk";
};

template <typename Period>
constexpr auto get_duration_unit() -> std::string_view {
  // clang-format off
  using std::chrono::years;
  using std::chrono::months;
  using std::chrono::weeks;
  using std::chrono::days;
  using std::chrono::hours;
  using std::chrono::minutes;
  using std::chrono::seconds;
  using std::chrono::milliseconds;
  using std::chrono::microseconds;
  using std::chrono::nanoseconds;
  // clang-format on

  if constexpr (std::ratio_equal_v<Period, years::period>) {
    return duration_unit::year;
  } else if constexpr (std::ratio_equal_v<Period, months::period>) {
    return duration_unit::month;
  } else if constexpr (std::ratio_equal_v<Period, weeks::period>) {
    return duration_unit::week;
  } else if constexpr (std::ratio_equal_v<Period, days::period>) {
    return duration_unit::day;
  } else if constexpr (std::ratio_equal_v<Period, hours::period>) {
    return duration_unit::hour;
  } else if constexpr (std::ratio_equal_v<Period, minutes::period>) {
    return duration_unit::minute;
  } else if constexpr (std::ratio_equal_v<Period, seconds::period>) {
    return duration_unit::second;
  } else if constexpr (std::ratio_equal_v<Period, milliseconds::period>) {
    return duration_unit::millisecond;
  } else if constexpr (std::ratio_equal_v<Period, microseconds::period>) {
    return duration_unit::microsecond;
  } else if constexpr (std::ratio_equal_v<Period, nanoseconds::period>) {
    return duration_unit::nanosecond;
  } else {
    return duration_unit::unknown;
  }
}

}  // namespace detail

template <typename Rep, typename Period>
struct inspector<std::chrono::duration<Rep, Period>> {
  static auto inspect(std::ostream& os,
                      const std::chrono::duration<Rep, Period>& obj)
      -> std::ostream& {
    return os << obj.count() << detail::get_duration_unit<Period>();
  }
};

}  // namespace insp
