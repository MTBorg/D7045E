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
	if(n->lChild == nullptr && n->rChild == nullptr){
		return {n->a, n->b, n->c};
	}

	auto lPoints = treeToPoints(n->lChild);
	auto rPoints = treeToPoints(n->rChild);
	auto res = lPoints;
	res.insert(res.end(), rPoints.begin(), rPoints.end());
	return res;
}
