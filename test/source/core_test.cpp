#include <ostream>
#include <sstream>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <inspector/core.hpp>

namespace user_defined_ns {

class intrusive_class {
  int begin_ = 0;
  int end_ = 10;

 public:
  auto inspect(std::ostream& os) const -> std::ostream& {
    return os << begin_ << "-" << end_;
  }
};

struct non_intrusive_class {
  int a = 5, b = 10;
};

struct non_intrusive_with_intrusive {
  intrusive_class ic;
};

class intrusive_with_non_intrusive {
  non_intrusive_class nic_;

 public:
  auto inspect(std::ostream& os) const -> std::ostream& {
    return os << "(" << insp::make_inspectable(nic_) << ")";
  }
};

auto inspect(std::ostream& os,
             const non_intrusive_class& obj) -> std::ostream& {
  return os << obj.a << "," << obj.b;
}

auto inspect(std::ostream& os,
             const non_intrusive_with_intrusive& obj) -> std::ostream& {
  return os << "(" << insp::make_inspectable(obj.ic) << ")";
}

}  // namespace user_defined_ns

TEST_CASE("Inspector core functionality", "[core]") {
  SECTION("with intrusive inspection") {
    const user_defined_ns::intrusive_class obj;
    const std::string expected = "0-10";

    SECTION("using make_inspectable") {
      std::stringstream ss;
      ss << insp::make_inspectable(obj);
      REQUIRE(ss.str() == expected);
    }

    SECTION("using to_string") {
      REQUIRE(insp::to_string(obj) == expected);
    }
  }

  SECTION("with non-intrusive inspection") {
    const user_defined_ns::non_intrusive_class obj;
    const std::string expected = "5,10";

    SECTION("using make_inspectable") {
      std::stringstream ss;
      ss << insp::make_inspectable(obj);
      REQUIRE(ss.str() == expected);
    }

    SECTION("using to_string") {
      REQUIRE(insp::to_string(obj) == expected);
    }
  }

  SECTION("with nested types") {
    SECTION("non-intrusive containing intrusive") {
      const user_defined_ns::non_intrusive_with_intrusive obj;
      const std::string expected = "(0-10)";

      SECTION("using make_inspectable") {
        std::stringstream ss;
        ss << insp::make_inspectable(obj);
        REQUIRE(ss.str() == expected);
      }

      SECTION("using to_string") {
        REQUIRE(insp::to_string(obj) == expected);
      }
    }

    SECTION("intrusive containing non-intrusive") {
      const user_defined_ns::intrusive_with_non_intrusive obj;
      const std::string expected = "(5,10)";

      SECTION("using make_inspectable") {
        std::stringstream ss;
        ss << insp::make_inspectable(obj);
        REQUIRE(ss.str() == expected);
      }

      SECTION("using to_string") {
        REQUIRE(insp::to_string(obj) == expected);
      }
    }
  }
}
