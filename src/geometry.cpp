// Copyright 2020 Gillwald

// C++ Standard Library
#include <cmath>
#include <vector>
#include <iterator>
#include <iostream>

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
	  // The output vector of cells
	  std::vector<Cell> out;	  

	  // If the input is less than or equal to one element, return the input
	  if (polygon.size() <= 1) {
	  	return polygon;
	  }

	  // Iterator to the next vertex
	  auto next_vrtx = polygon.begin();

	  for (const auto &vertex:polygon) {
	  	// If the next vertex is not the end iterator, advance the next_vertex to point to the next iterator
	  	if (next_vrtx != polygon.end()) {
	  		std::advance(next_vrtx,1);
	  	} 
	  	// After advancing, if the iterator points to the end, go back to the beginning, essentially closing the polygon
	  	if (next_vrtx == polygon.end()) {
	  		next_vrtx = polygon.begin();
	  	}

	  	// Generate the pixels from one vertex to the next
	  	auto temp = raytrace(vertex, (*next_vrtx), size_x);

	  	// Remove the last element of the vector because the next vertex will use it as a starting point i.e. don't duplicate pixels
	  	temp.pop_back();

	  	// Push the pixels into the out vector
	  	for (const auto &pixel:temp) {
	  		out.push_back(pixel);
	  	}

	  }
	  return out;
	}	


}  // namespace geometry