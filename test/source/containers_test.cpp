#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <inspector/containers.hpp>  // IWYU pragma: keep
#include <inspector/core.hpp>

TEST_CASE("Inspector container functionality", "[containers]") {
  SECTION("std::vector") {
    SECTION("with integers") {
      const std::vector<int> vec{1, 2, 3};
      REQUIRE(insp::to_string(vec) == "[1, 2, 3]");
    }

    SECTION("with strings") {
      const std::vector<std::string> vec{"hello", "world"};
      REQUIRE(insp::to_string(vec) == "[hello, world]");
    }

    SECTION("empty vector") {
      const std::vector<int> vec;
      REQUIRE(insp::to_string(vec) == "[]");
    }

    SECTION("nested vectors") {
      const std::vector<std::vector<int>> vec{{1, 2}, {3, 4}};
      REQUIRE(insp::to_string(vec) == "[[1, 2], [3, 4]]");
    }
  }

  SECTION("std::list and std::forward_list") {
    SECTION("std::list") {
      const std::list<int> lst{1, 2, 3};
      REQUIRE(insp::to_string(lst) == "[1, 2, 3]");
    }

    SECTION("std::forward_list") {
      const std::forward_list<int> lst{1, 2, 3};
      REQUIRE(insp::to_string(lst) == "[1, 2, 3]");
    }
  }

  SECTION("std::deque") {
    const std::deque<int> deq{1, 2, 3};
    REQUIRE(insp::to_string(deq) == "[1, 2, 3]");
  }

  SECTION("std::set containers") {
    SECTION("std::set") {
      const std::set<int> s{3, 1, 2};
      REQUIRE(insp::to_string(s) == "[1, 2, 3]");
    }

    SECTION("std::multiset") {
      const std::multiset<int> s{1, 2, 2, 3};
      REQUIRE(insp::to_string(s) == "[1, 2, 2, 3]");
    }

    SECTION("std::unordered_set") {
      const std::unordered_set<int> s{1, 2, 3};
      const std::string result = insp::to_string(s);
      // Order is not guaranteed, but content is
      REQUIRE(result.size() == 9);  // "[1, 2, 3]"
      REQUIRE(result.front() == '[');
      REQUIRE(result.back() == ']');
    }
  }

  SECTION("std::map containers") {
    SECTION("std::map") {
      const std::map<std::string, int> m{{"one", 1}, {"two", 2}};
      REQUIRE(insp::to_string(m) == "{one: 1, two: 2}");
    }

    SECTION("std::multimap") {
      const std::multimap<std::string, int> m{{"one", 1}, {"one", 2}};
      REQUIRE(insp::to_string(m) == "{one: 1, one: 2}");
    }

    SECTION("std::unordered_map") {
      const std::unordered_map<std::string, int> m{{"one", 1}, {"two", 2}};
      const std::string result = insp::to_string(m);
      REQUIRE(result.front() == '{');
      REQUIRE(result.back() == '}');
    }
  }

  SECTION("Container adapters") {
    SECTION("std::stack") {
      std::stack<int> s;
      s.push(1);
      s.push(2);
      s.push(3);
      REQUIRE(insp::to_string(s) == "[3, 2, 1]");
    }

    SECTION("std::queue") {
      std::queue<int> q;
      q.push(1);
      q.push(2);
      q.push(3);
      REQUIRE(insp::to_string(q) == "[1, 2, 3]");
    }

    SECTION("std::priority_queue") {
      std::priority_queue<int> pq;
      pq.push(1);
      pq.push(3);
      pq.push(2);
      REQUIRE(insp::to_string(pq) == "[3, 2, 1]");
    }
  }
}
