#include <string>
#include <tuple>
#include <utility>

#include <catch2/catch_test_macros.hpp>
#include <inspector/core.hpp>
#include <inspector/utility.hpp>  // IWYU pragma: keep

TEST_CASE("Inspect std::pair", "[utility]") {
  SECTION("basic types") {
    SECTION("int and int") {
      const auto p = std::make_pair(42, 24);
      REQUIRE(inspector::to_string(p) == "(42, 24)");
    }

    SECTION("string and int") {
      const auto p = std::make_pair("hello", 42);
      REQUIRE(inspector::to_string(p) == "(hello, 42)");
    }

    SECTION("string and string") {
      const auto p = std::make_pair(std::string("hello"), std::string("world"));
      REQUIRE(inspector::to_string(p) == "(hello, world)");
    }
  }

  SECTION("nested pairs") {
    const auto inner = std::make_pair(1, 2);
    const auto outer = std::make_pair(inner, 3);
    REQUIRE(inspector::to_string(outer) == "((1, 2), 3)");
  }
}

TEST_CASE("Inspect std::tuple", "[utility]") {
  SECTION("basic tuples") {
    SECTION("empty tuple") {
      const std::tuple<> t{};
      REQUIRE(inspector::to_string(t) == "()");
    }

    SECTION("single element") {
      const auto t = std::make_tuple(42);
      REQUIRE(inspector::to_string(t) == "(42)");
    }

    SECTION("two elements") {
      const auto t = std::make_tuple(42, "hello");
      REQUIRE(inspector::to_string(t) == "(42, hello)");
    }

    SECTION("multiple elements") {
      const auto t = std::make_tuple(1, "hello", 3.14, true);
      REQUIRE(inspector::to_string(t) == "(1, hello, 3.14, 1)");
    }
  }

  SECTION("nested structures") {
    SECTION("tuple containing pair") {
      const auto p = std::make_pair(1, 2);
      const auto t = std::make_tuple(p, 3);
      REQUIRE(inspector::to_string(t) == "((1, 2), 3)");
    }

    SECTION("tuple containing tuple") {
      const auto inner = std::make_tuple(1, 2);
      const auto outer = std::make_tuple(inner, 3);
      REQUIRE(inspector::to_string(outer) == "((1, 2), 3)");
    }

    SECTION("complex nesting") {
      const auto p = std::make_pair(1, 2);
      const auto t1 = std::make_tuple(3, 4);
      const auto complex = std::make_tuple(p, t1, 5);
      REQUIRE(inspector::to_string(complex) == "((1, 2), (3, 4), 5)");
    }
  }
}
