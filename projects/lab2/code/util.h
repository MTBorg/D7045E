#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <algorithm>
#include <math.h>
#include <glm/glm.hpp>   
#include <iostream>

#include "types.h"
#include "node.h"

/**
 * Sort points.
 *
 * Sort first by strictly less than then (if equal sort by y)
 */
inline void sortPoints(std::vector<glvec>& points){
	std::sort(
		points.begin(),
		points.end(),
		[](const glvec& v1, const glvec& v2){
			return (v1.x == v2.x) ? (v1.y < v2.y) : (v1.x < v2.x);
		}
	);
}

/*
 * Check if the point c lies to the left of (but not on) the line containing 
 * the line segment a to b.
 */
inline bool pointLeftOfLine(
		const glvec& a,
		const glvec& b,
		const glvec& c
	){
	return (b.x - a.x)*(c.y - a.y) > (b.y - a.y)*(c.x-a.x);
}

/*
 * Check if the point c lies on the line containing the line segment a to b,
 * but only on the side starting from a going towards b.
 */
inline bool pointOnLine(
		const glvec& point,
		const glvec& a,
		const glvec& b
	){
	return ((b.x - a.x)*(point.y - a.y) == (b.y - a.y)*(point.x-a.x)) &&
		(glm::normalize(b-a) == glm::normalize(point-a));
}

int pickPointNotOnConvexHull(const std::vector<glvec>& points, const std::vector<glvec>& hull);

inline bool pointInsideTriangle(
		const glvec& point,
		const glvec& a,
		const glvec& b,
		const glvec& c){
	return 
		(
			pointLeftOfLine(a,b, point) &&
			pointLeftOfLine(b,c,point) && 
			pointLeftOfLine(c,a, point)
		) ||
		(
			!pointLeftOfLine(a,b, point) &&
			!pointLeftOfLine(b,c,point) && 
			!pointLeftOfLine(c,a, point)
		);
}

// Check if a point is in sector between the clockwise sector beetween the lines
// ci->c and cm->c
bool pointInSector(const glvec& point, const glvec& c, const glvec& ci, const glvec& cm);

#endif
