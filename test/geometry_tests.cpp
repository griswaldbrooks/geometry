// Copyright 2020 Gillwald

// C++ Standard Library
#include <vector>

// Gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Code to test
#include "gillwald/geometry.hpp"

namespace geometry {

void printPixels(std::vector<std::vector<int>> pixels){
	std::cout << "\n";
	for (const auto &pixel:pixels ) {
		std::cout << "(" << pixel[0] << ", " << pixel[1] << ")\n";		
	}		
	std::cout << "\n";
}

bool allXOrYCoorSame(int x_or_y, std::vector<std::vector<int>> pixels){
	if (x_or_y == 0) { // Check X coordinates
		x_or_y = 0;
	} else { // Check Y coordinatesd
		x_or_y = 1;
	}

	auto shouldBeEqualTo = pixels[0][x_or_y];

	float sum = 0;

	for (const auto &pixel:pixels) {
		sum += pixel[x_or_y];
	}

	float avg = sum/static_cast<float>(pixels.size());

	if (avg == shouldBeEqualTo) {
		return true;
	} else {
		return false;
	}

}

bool checkFirstOrLastPoint(int firstOrLastPoint, int x_shouldbe, int y_shouldbe, std::vector<std::vector<int>> v) {
	std::vector<std::vector<int>>::iterator ptr;
	if (firstOrLastPoint == 0) {
		ptr = v.begin();
	} else {
		ptr = v.end() - 1;
	}

	if (((*ptr)[0] == x_shouldbe) && ((*ptr)[1] == y_shouldbe)) {
		return true;
	} else {
		return false;
	}

}

TEST(Point2DPlanning_Griz_Test, bresenham_conversion_test) {
	// Get the points for the line connecting (0,0) and (5,0)
	auto v = bresenham_conversion(0, 0, 5, 0);

	// Check if the vector size is 6 points 
	ASSERT_EQ(v.size(), 6);

	// Check if the first point is (0,0)
	ASSERT_EQ(checkFirstOrLastPoint(0, 0, 0, v), true);

	// Check if the last point is (5,0)
	ASSERT_EQ(checkFirstOrLastPoint(1, 5, 0, v), true);
}

TEST(Point2DPlanning_Griz_Test, bresenham_conversion_horz_line_test) {
	// Create a horizontal line between points (0,0) and (5,0)
	auto v = bresenham_conversion(0, 0, 5, 0);
		
	// Check there are 6 points
	ASSERT_EQ(v.size(), 6);

	// Check that all the y coordinates are the same (indicates horz line)
	ASSERT_EQ(allXOrYCoorSame(1,v), true);	

	// Create a horizontal line from (4,5) to (-1,5)
	v = bresenham_conversion(4, 5, -1, 5);
	
	// Check there are 6 points
	ASSERT_EQ(v.size(), 6);	

	// Check that all the y coordinates are the same (indicates horz line)
	ASSERT_EQ(allXOrYCoorSame(1,v), true);	
}

TEST(Point2DPlanning_Griz_Test, bresenham_conversion_vert_line_test) {
	// Create a vertical line from (-2,-3) to (-2, 2)
	auto v = bresenham_conversion(-2,-3,-2,2);	

	// Check there are 6 points
	ASSERT_EQ(v.size(), 6);

	// Check that all of the x coordinates are the same (indicates vertical line)
	ASSERT_EQ(allXOrYCoorSame(0,v), true);	

	v = bresenham_conversion(1, 2, 1, -3);
	
	// Check that there are 6 points
	ASSERT_EQ(v.size(), 6);	

	// Check that all of the x coordinates are the same (indicates vertical line)
	ASSERT_EQ(allXOrYCoorSame(0,v), true);	
}

TEST(Point2DPlanning_Griz_Test, bresenham_conversion_point_test) {
	// Get the points for the line connecting (0,0) and (0,0)
	auto v = bresenham_conversion(0, 0, 0, 0);

	// Check only one point was produced
	ASSERT_EQ(v.size(), 1);

	// Check the point is (0,0)
	ASSERT_EQ(checkFirstOrLastPoint(0, 0, 0, v), true);	

	// Get the points for the line connecting (3,4) and (3,4)
	v = bresenham_conversion(3, 4, 3, 4);

	// Check only one point was produced
	ASSERT_EQ(v.size(), 1);

	// Check the point is (3,4)
	ASSERT_EQ(checkFirstOrLastPoint(0, 3, 4, v), true);

}

TEST(Point2DPlanning_Griz_Test, bresenham_conversion_octant1_test) {
	// Get the points for the line connecting (0,0) and (5,3)
	auto v = bresenham_conversion(0, 0, 5, 3);

	// Check only one point was produced
	ASSERT_EQ(v.size(), 6);

	// Check the first point is (0,0)
	ASSERT_EQ(checkFirstOrLastPoint(0, 0, 0, v), true);	

	// Check the last point is (0,0)
	ASSERT_EQ(checkFirstOrLastPoint(1, 5, 3, v), true);	

	// Get the points for the line connecting (5,3) and (0,0)
	v = bresenham_conversion(5, 3, 0, 0);

	// Check only one point was produced
	ASSERT_EQ(v.size(), 6);

	// Check the first point is (0,0)
	ASSERT_EQ(checkFirstOrLastPoint(0, 5, 3, v), true);	

	// Check the last point is (0,0)
	ASSERT_EQ(checkFirstOrLastPoint(1, 0, 0, v), true);	

}

}  // namespace geometry

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
