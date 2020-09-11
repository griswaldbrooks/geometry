// Copyright 2020 Gillwald

// C++ Standard Library
#include <array>
#include <cmath>
#include <vector>

// Gillwald
#include <gillwald/geometry.hpp>

struct Cell {
  int x;
  int y;
};

namespace geometry {

	std::vector<Cell> bresenham_conversion(int x0, int y0, int x1, int y1){
		return bresenham_conversion(Cell{x0, y0}, Cell{x1, y1});
	}

	std::vector<Cell> bresenham_conversion(const Cell& start, const Cell& end){

	  // Vector of points
	  std::vector<Cell> v;

	  // Beginning point
	  int p0 [2] = {start.x, start.y};

	  // Ending point
	  int p1 [2] = {end.x, end.y};

	  // Change in x and y from beginning to end
	  int deltas [2] = {(end.x - start.x), (end.y - start.y)};

	  // Absolute values of  the changes
	  int changes [2] = {abs(deltas[0]),abs(deltas[1])};

	  // Lambda that emulates signum
	  auto sgn = [](auto a){return (a > 0) - (a < 0);};

	  // Which direction to step towards for the x and y functions
	  int steps [2] = {sgn(deltas[0]), sgn(deltas[1])};

	  // Array that dictates the dominant direction
    const auto idx = changes[0] > changes[1] ? std::array<int, 2>{0, 1} : std::array<int, 2>{1, 0};

	  // error scaled off of change in dominant direction
	  float err = (float)changes[idx[0]]/2.0;

	  // points that will be pushed back
	  int point [2] = {p0[0], p0[1]};

	  // while the dominant direction coordinate isn't equal to the ending coordinate
	  while (point[idx[0]] != p1[idx[0]]) {

	    // Create and push back vector into final vector
	    Cell temp {point[0], point[1]};

	    v.push_back(temp);

	    // bresenham magic
	    err -= changes[idx[1]];

	    if (err < 0) {

	      point[idx[1]] += steps[idx[1]];

	      err += changes[idx[0]];

	    }

	    point[idx[0]] += steps[idx[0]];

	  }

	  // Push final point
	  Cell temp {p1[0], p1[1]};

	  v.push_back(temp);

	  return v;

	}

	std::vector<Cell> raytrace(const Cell& start, const Cell& end, int max_length) {
	  if (max_length < 1) {
	  	return {};
	  }
	  // Get the interpolated pixels bresenham
	  const auto pixels = bresenham_conversion(start, end);

	  return {pixels.begin(), pixels.begin() + std::min(static_cast<int>(pixels.size()),max_length)};

	}

}  // namespace geometry
