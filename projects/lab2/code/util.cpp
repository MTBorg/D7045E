#include "util.h"

#include "types.h"

#include <iostream>

int pickPointNotOnConvexHull(const std::vector<glvec>& points, const std::vector<glvec>& hull){
	for(auto it = points.begin(); it != points.end(); ++it){
		auto p = find(hull.begin(), hull.end(), *it);
		if(p == hull.end()){
			return it - points.begin();
		}
	}
	return -1;
}

bool pointInSector(const glvec& point, const glvec& c, const glvec& ci, const glvec& cm){
	if(pointLeftOfLine(cm, c, ci)){
		return !pointLeftOfLine(cm, c, point) || pointLeftOfLine(ci, c, point);
	}
	return pointLeftOfLine(ci, c, point) && !pointLeftOfLine(cm, c, point);
}
