// Copyright 2020 Gillwald

// C++ Standard Library
#include <vector>

// Gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Code to test
#include "gillwald/geometry.hpp"

namespace geometry {

TEST(BresenhamTests, SamePoint) {
  // GIVEN two origin points
  // WHEN computing the pixels to iterpolate
  const auto pixels = bresenham_conversion(0, 0, 0, 0);

  // THEN it will just be the origin point.
  std::vector<std::vector<int>> expected = {{0, 0}};
  EXPECT_THAT(pixels, ::testing::ElementsAreArray(expected));
}

}  // namespace geometry

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
