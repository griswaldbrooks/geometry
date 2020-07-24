// Copyright 2020 Gillwald

#pragma once

// C++ Standard Library
#include <vector>

namespace geometry {
  /**
   * @brief Creates discretized line between two end points
   * @param x0 X coordinate of starting point
   * @param y0 Y coordinate of starting point
   * @param x1 X coordinate of ending point
   * @param y1 Y coordinate of ending point
   * @returns Pixel coordinates representing line
   */
  std::vector<std::vector<int>> bresenham_conversion(int x0, int y0, int x1, int y1);
}  // namespace geometry
