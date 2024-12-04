#include <optional>
#include <ostream>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <inspector/core.hpp>
#include <inspector/optional.hpp>  // IWYU pragma: keep

TEST_CASE("Inspect std::optional", "[optional]") {
  SECTION("with nullopt") {
    const std::optional<int> obj;
    REQUIRE(insp::to_string(obj) == "nullopt");
  }

  SECTION("with int value") {
    const std::optional<int> obj = 42;
    REQUIRE(insp::to_string(obj) == "42");
  }

  SECTION("with string value") {
    const std::optional<std::string> obj = "hello";
    REQUIRE(insp::to_string(obj) == "hello");
  }

  SECTION("with nested optional") {
    const std::optional<std::optional<int>> obj = std::optional<int>{42};
    REQUIRE(insp::to_string(obj) == "42");
  }

  SECTION("with nested nullopt") {
    const std::optional<std::optional<int>> obj = std::nullopt;
    REQUIRE(insp::to_string(obj) == "nullopt");
  }
}

TEST_CASE("Inspect std::optional with custom type", "[optional]") {
  struct custom_type {
    int value = 42;
    auto inspect(std::ostream& os) const -> std::ostream& {
      return os << "Custom(" << value << ")";
    }
  };

  SECTION("with value") {
    const std::optional<custom_type> obj = custom_type{};
    REQUIRE(insp::to_string(obj) == "Custom(42)");
  }

  SECTION("without value") {
    const std::optional<custom_type> obj;
    REQUIRE(insp::to_string(obj) == "nullopt");
  }
}
