#include <chrono>
#include <iomanip>
#include <ios>
#include <ratio>
#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <inspector/chrono.hpp>  // IWYU pragma: keep
#include <inspector/core.hpp>

TEST_CASE("Inspect std::chrono::duration", "[chrono]") {
  SECTION("integral representation") {
    SECTION("basic time units") {
      REQUIRE(insp::to_string(std::chrono::years{1}) == "1y");
      REQUIRE(insp::to_string(std::chrono::months{1}) == "1mo");
      REQUIRE(insp::to_string(std::chrono::weeks{1}) == "1w");
      REQUIRE(insp::to_string(std::chrono::days{1}) == "1d");
      REQUIRE(insp::to_string(std::chrono::hours{1}) == "1h");
      REQUIRE(insp::to_string(std::chrono::minutes{1}) == "1min");
      REQUIRE(insp::to_string(std::chrono::seconds{1}) == "1s");
      REQUIRE(insp::to_string(std::chrono::milliseconds{1}) == "1ms");
      REQUIRE(insp::to_string(std::chrono::microseconds{1}) == "1us");
      REQUIRE(insp::to_string(std::chrono::nanoseconds{1}) == "1ns");
    }

    SECTION("negative values") {
      REQUIRE(insp::to_string(std::chrono::seconds{-1}) == "-1s");
      REQUIRE(insp::to_string(std::chrono::minutes{-2}) == "-2min");
    }

    SECTION("zero values") {
      REQUIRE(insp::to_string(std::chrono::hours{0}) == "0h");
      REQUIRE(insp::to_string(std::chrono::days{0}) == "0d");
    }
  }

  SECTION("floating point representation") {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);

    SECTION("seconds with floating point") {
      using fp_seconds =
          std::chrono::duration<double, std::chrono::seconds::period>;
      ss << insp::make_inspectable(fp_seconds{1.23});
      REQUIRE(ss.str() == "1.23s");
    }

    SECTION("milliseconds with floating point") {
      using fp_milliseconds =
          std::chrono::duration<double, std::chrono::milliseconds::period>;
      ss.str("");
      ss << insp::make_inspectable(fp_milliseconds{1.23});
      REQUIRE(ss.str() == "1.23ms");
    }

    SECTION("microseconds with floating point") {
      using fp_microseconds =
          std::chrono::duration<double, std::chrono::microseconds::period>;
      ss.str("");
      ss << insp::make_inspectable(fp_microseconds{1.23});
      REQUIRE(ss.str() == "1.23us");
    }
  }

  SECTION("custom durations") {
    SECTION("week equivalent duration") {
      // 1 week in seconds (7 * 24 * 60 * 60)
      using week_in_seconds = std::ratio<604800>;
      using custom_week = std::chrono::duration<int, week_in_seconds>;
      REQUIRE(insp::to_string(custom_week{1}) == "1w");
    }

    SECTION("unknown duration") {
      // 5 seconds - not matching any standard duration
      using five_seconds = std::ratio<5>;
      using custom_duration = std::chrono::duration<int, five_seconds>;
      REQUIRE(insp::to_string(custom_duration{1}) == "1unk");

      // 2.5 days - not matching any standard duration
      using two_and_half_days = std::ratio<216000>;  // 2.5 * 24 * 60 * 60
      using custom_days = std::chrono::duration<int, two_and_half_days>;
      REQUIRE(insp::to_string(custom_days{1}) == "1unk");
    }
  }
}
