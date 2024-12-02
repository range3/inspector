cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    inspector
    VERSION 0.1.0
    DESCRIPTION "A header-only library for converting any object to string representation"
    HOMEPAGE_URL "https://github.com/range3/inspector"
    LANGUAGES NONE
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(inspector_inspector INTERFACE)
add_library(inspector::inspector ALIAS inspector_inspector)

set_property(
    TARGET inspector_inspector PROPERTY
    EXPORT_NAME inspector
)

target_include_directories(
    inspector_inspector ${warning_guard}
    INTERFACE
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(inspector_inspector INTERFACE cxx_std_20)

# find_package(fmt REQUIRED)
# target_link_libraries(inspector_inspector INTERFACE fmt::fmt)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT inspector_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of inspector"
  )
endif()

include(cmake/dev-mode.cmake)
