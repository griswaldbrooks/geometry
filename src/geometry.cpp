// Copyright 2020 Gillwald

// C++ Standard Library
#include <algorithm>
#include <cmath>
#include <vector>
#include <iterator>
#include <iostream>
#include <numeric>

// Gillwald
#include <gillwald/geometry.hpp>

namespace geometry {


	std::vector<std::vector<int>> bresenham_conversion(int x0, int y0, int x1, int y1){

	  // Vector of points
	  std::vector<std::vector<int>> v;

	  // Beginning point
	  int p0 [2] = {x0, y0};

	  // Ending point
	  int p1 [2] = {x1, y1};

	  // Change in x and y from beginning to end
	  int deltas [2] = {(x1 - x0), (y1 - y0)};

	  // Absolute values of  the changes
	  int changes [2] = {abs(deltas[0]),abs(deltas[1])};

	  // Lambda that emulates signum
	  auto sgn = [](auto a){return (a > 0) - (a < 0);};

	  // Which direction to step towards for the x and y functions
	  int steps [2] = {sgn(deltas[0]), sgn(deltas[1])};

	  // Array that dictates the dominant direction
	  int idx [2] = {0};

	  if (changes[0] > changes[1]) {
	    idx[0] = 0;
	    idx[1] = 1;
	  } else {
	    idx[0] = 1;
	    idx[1] = 0;
	  }

	  // error scaled off of change in dominant direction
	  float err = (float)changes[idx[0]]/2.0;

	  // points that will be pushed back
	  int point [2] = {p0[0], p0[1]};

	  // while the dominant direction coordinate isn't equal to the ending coordinate
	  while (point[idx[0]] != p1[idx[0]]) {

	    // Create and push back vector into final vector
	    std::vector<int> temp {point[0], point[1]};

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
	  std::vector<int> temp {p1[0], p1[1]};

	  v.push_back(temp);

	  return v;

	}

	std::vector<Cell> bresenham_conversion(const Cell &start, const Cell &end){

		const auto pixels = bresenham_conversion(start.x, start.y, end.x, end.y);

		std::vector<Cell> cells;

		for (const auto &pixel:pixels) {
			cells.emplace_back(Cell{pixel[0], pixel[1]});
		}

		return cells;

	}

	std::vector<Cell> raytrace(const Cell& start, const Cell& end, int max_length) {
	  if (max_length < 1) {
	  	return {};
	  }
	  // Get the interpolated pixels bresenham
	  const auto pixels = bresenham_conversion(start, end);

	  return {pixels.begin(), pixels.begin() + std::min(static_cast<int>(pixels.size()),max_length)};

	}

	std::vector<Cell> polygonOutlineCells(const std::vector<Cell>& polygon, int size_x) {
		// If the input is less than or equal to one element, return the input
		if (polygon.size() <= 1) {
			return polygon;
		}

	  // The output vector of cells
	  std::vector<std::vector<Cell>> traces;
		traces.resize(polygon.size());

    std::transform(polygon.begin(), std::prev(polygon.end()), std::next(polygon.begin()), traces.begin(), [] (const Cell& a, const Cell& b) {
			return raytrace(a, b, std::numeric_limits<int>::max());
		});

		auto out = std::accumulate(traces.begin(), traces.end(), std::vector<Cell>(), [](std::vector<Cell> a, const std::vector<Cell>& b) {
        a.insert(a.end(), b.begin(), b.end());
        return a;
    });
		out.push_back(polygon.back());
		return out;
	}


}  // namespace geometry
