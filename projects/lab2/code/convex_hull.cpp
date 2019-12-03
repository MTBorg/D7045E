#include "convex_hull.h"
#include <iostream>
#include <algorithm>

#include "util.h"

std::vector<glvec> convexHull(const std::vector<glvec> points){
	//Sort the points
	auto sortedPoints = points;
	sortPoints(sortedPoints);
	/* std::reverse(sortedPoints.begin(), sortedPoints.end()); */

	auto upperHull = std::vector<glvec>(), lowerHull = std::vector<glvec>();

	//Construct upper hull
	for(const auto& point: sortedPoints){
		while(
				upperHull.size() >= 2 &&
				pointLeftOfLine(*(upperHull.end()-2), *(upperHull.end()-1), point)
			){
				upperHull.pop_back();
		}
		upperHull.push_back(point);
	}


	//Construct lower hull
	for(auto it = sortedPoints.rbegin(); it != sortedPoints.rend(); ++it){
		while(
				lowerHull.size() >= 2 &&
				pointLeftOfLine(*(lowerHull.end()-2), *(lowerHull.end()-1), *it)
			){
				lowerHull.pop_back();
		}
		lowerHull.push_back(*it);
	}

	// Remove the last points to remove duplicates
	upperHull.pop_back();
	lowerHull.pop_back();

	// Concatenate the hulls
	upperHull.insert(upperHull.end(), lowerHull.begin(), lowerHull.end());
	return upperHull;
}
