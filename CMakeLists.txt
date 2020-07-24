cmake_minimum_required(VERSION 2.6)

project(gillwald-geometry)

add_compile_options(-std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers)

find_package(GTest REQUIRED)
include_directories(include ${GTEST_INCLUDE_DIRS})

add_library(gillwald_geometry src/geometry.cpp)

add_executable(geometry_tests test/geometry_tests.cpp)
target_link_libraries(geometry_tests
  ${GTEST_LIBRARIES}
  gmock
  pthread
  gillwald_geometry)
