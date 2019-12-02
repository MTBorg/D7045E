#include "validation.h"
#include "types.h"

bool validation::originIsInConvexHull(const std::vector<glvec>& points){
	//Find min/max values
	float minX = 1, minY = 1, maxX = -1, maxY = -1;
	for(const auto& point: points){
		if(point.x < minX) minX = point.x;
		if(point.x > maxX) maxX = point.x;
		if(point.y < minY) minY = point.y;
		if(point.y > maxY) maxY = point.y;
	}

	// Check if min/max values surround origin
	return (
		minX < 0 &&
		maxX > 0 &&
		minY < 0 &&
		maxY > 0
	);
}

bool validation::duplicatePoints(const std::vector<glvec>& points){
	for(auto it1 = points.begin(); it1 != points.end(); ++it1){
		for(auto it2 = it1; it2 != points.end(); ++it2){
			if(*it1 == *it2 && it1 != it2) return true;
		}
	}
	return false;
}
