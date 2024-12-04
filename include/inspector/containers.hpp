#pragma once

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "core.hpp"

namespace insp {
namespace detail {

template <typename Iter>
auto array_like_inspect(std::ostream& os,
                        Iter begin,
                        Iter end) -> std::ostream& {
  os << '[';
  if (begin != end) {
    os << make_inspectable(*begin++);
    for (auto it = begin; it != end; ++it) {
      os << ", " << make_inspectable(*it);
    }
  }
  os << ']';
  return os;
}

template <typename MapIter>
auto map_like_inspect(std::ostream& os,
                      MapIter begin,
                      MapIter end) -> std::ostream& {
  os << '{';
  if (begin != end) {
    os << make_inspectable(begin->first) << ": "
       << make_inspectable(begin->second);
    ++begin;
    for (auto it = begin; it != end; ++it) {
      os << ", " << make_inspectable(it->first) << ": "
         << make_inspectable(it->second);
    }
  }
  os << '}';
  return os;
}

}  // namespace detail

template <typename T>
struct inspector<std::vector<T>> {
  static auto inspect(std::ostream& os,
                      const std::vector<T>& obj) -> std::ostream& {
    return detail::array_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename T, std::size_t N>
struct inspector<std::array<T, N>> {
  static auto inspect(std::ostream& os,
                      const std::array<T, N>& obj) -> std::ostream& {
    return detail::array_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename T>
struct inspector<std::deque<T>> {
  static auto inspect(std::ostream& os,
                      const std::deque<T>& obj) -> std::ostream& {
    return detail::array_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename T>
struct inspector<std::forward_list<T>> {
  static auto inspect(std::ostream& os,
                      const std::forward_list<T>& obj) -> std::ostream& {
    return detail::array_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename T>
struct inspector<std::list<T>> {
  static auto inspect(std::ostream& os,
                      const std::list<T>& obj) -> std::ostream& {
    return detail::array_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename K, typename V>
struct inspector<std::map<K, V>> {
  static auto inspect(std::ostream& os,
                      const std::map<K, V>& obj) -> std::ostream& {
    return detail::map_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename K, typename V>
struct inspector<std::unordered_map<K, V>> {
  static auto inspect(std::ostream& os,
                      const std::unordered_map<K, V>& obj) -> std::ostream& {
    return detail::map_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename K, typename V>
struct inspector<std::multimap<K, V>> {
  static auto inspect(std::ostream& os,
                      const std::multimap<K, V>& obj) -> std::ostream& {
    return detail::map_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename K, typename V>
struct inspector<std::unordered_multimap<K, V>> {
  static auto inspect(std::ostream& os,
                      const std::unordered_multimap<K, V>& obj)
      -> std::ostream& {
    return detail::map_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename T>
struct inspector<std::set<T>> {
  static auto inspect(std::ostream& os,
                      const std::set<T>& obj) -> std::ostream& {
    return detail::array_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename T>
struct inspector<std::unordered_set<T>> {
  static auto inspect(std::ostream& os,
                      const std::unordered_set<T>& obj) -> std::ostream& {
    return detail::array_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename T>
struct inspector<std::multiset<T>> {
  static auto inspect(std::ostream& os,
                      const std::multiset<T>& obj) -> std::ostream& {
    return detail::array_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename T>
struct inspector<std::unordered_multiset<T>> {
  static auto inspect(std::ostream& os,
                      const std::unordered_multiset<T>& obj) -> std::ostream& {
    return detail::array_like_inspect(os, obj.begin(), obj.end());
  }
};

template <typename T>
struct inspector<std::stack<T>> {
  static auto inspect(std::ostream& os,
                      const std::stack<T>& obj) -> std::ostream& {
    auto copy = obj;  // Explicit copy as the inspection is destructive
    os << '[';
    if (!copy.empty()) {
      os << make_inspectable(copy.top());
      copy.pop();
      while (!copy.empty()) {
        os << ", " << make_inspectable(copy.top());
        copy.pop();
      }
    }
    return os << ']';
  }
};

template <typename T>
struct inspector<std::queue<T>> {
  static auto inspect(std::ostream& os,
                      const std::queue<T>& obj) -> std::ostream& {
    auto copy = obj;  // Explicit copy as the inspection is destructive
    os << '[';
    if (!copy.empty()) {
      os << make_inspectable(copy.front());
      copy.pop();
      while (!copy.empty()) {
        os << ", " << make_inspectable(copy.front());
        copy.pop();
      }
    }
    return os << ']';
  }
};

template <typename T>
struct inspector<std::priority_queue<T>> {
  static auto inspect(std::ostream& os,
                      const std::priority_queue<T>& obj) -> std::ostream& {
    auto copy = obj;  // Explicit copy as the inspection is destructive
    os << '[';
    if (!copy.empty()) {
      os << make_inspectable(copy.top());
      copy.pop();
      while (!copy.empty()) {
        os << ", " << make_inspectable(copy.top());
        copy.pop();
      }
    }
    return os << ']';
  }
};

}  // namespace insp
