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

/* std::vector<glvec> treeToPoints(const Node* n){ */
/* 	if(n->s1 == nullptr && n->s2 == nullptr && n->s3 == nullptr){ */
/* 		return {n->ci, n->cm, n->cj}; */
/* 	} */

/* 	auto res = std::vector<glvec>(); */
/* 	if(n->s1 != nullptr){ */
/* 		auto points = treeToPoints(n->s1); */
/* 		res.insert(res.end(), points.begin(), points.end()); */
/* 	} */
/* 	if(n->s2 != nullptr){ */
/* 		auto points = treeToPoints(n->s2); */
/* 		res.insert(res.end(), points.begin(), points.end()); */
/* 	} */
/* 	if(n->s3 != nullptr){ */
/* 		auto points = treeToPoints(n->s3); */
/* 		res.insert(res.end(), points.begin(), points.end()); */
/* 	} */
/* 	return res; */
/* } */


bool pointInSector(const glvec& point, const glvec& c, const glvec& ci, const glvec& cm){
	/* printf("p-x: %f, p-y: %f\n", point.x, point.y); */
	/* printf("c-x: %f, c-y: %f\n", c.x, c.y); */
	/* printf("ci-x: %f, ci-y: %f\n", ci.x, ci.y); */
	/* printf("cm-x: %f, cm-y: %f\n", cm.x, cm.y); */
	/* printf("\n"); */
	if(pointLeftOfLine(cm, c, ci)){
		return !pointLeftOfLine(cm, c, point) || pointLeftOfLine(ci, c, point);
	}
	return pointLeftOfLine(ci, c, point) && !pointLeftOfLine(cm, c, point);
}
