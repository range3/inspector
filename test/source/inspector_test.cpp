#include "inspector/inspector.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Name is inspector", "[library]")
{
  REQUIRE(name() == "inspector");
}
