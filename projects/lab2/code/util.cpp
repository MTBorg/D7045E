#include "util.h"

#include "types.h"

int pickPointNotOnConvexHull(const std::vector<glvec>& points, const std::vector<glvec>& hull){
	for(auto it = points.begin(); it != points.end(); ++it){
		auto p = find(hull.begin(), hull.end(), *it);
		if(p == hull.end()){
			return it - points.begin();
		}
	}
	return -1;
}

std::vector<glvec> treeToPoints(const Node* n){
	if(n->s1 == nullptr && n->s2 == nullptr && n->s3 == nullptr){
		return {n->ci, n->cm, n->cj};
	}

	auto res = std::vector<glvec>();
	if(n->s1 != nullptr){
		auto points = treeToPoints(n->s1);
		res.insert(res.end(), points.begin(), points.end());
	}
	if(n->s2 != nullptr){
		auto points = treeToPoints(n->s2);
		res.insert(res.end(), points.begin(), points.end());
	}
	if(n->s3 != nullptr){
		auto points = treeToPoints(n->s3);
		res.insert(res.end(), points.begin(), points.end());
	}
	return res;
}
