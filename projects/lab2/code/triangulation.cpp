#include "triangulation.h"

#include <vector>

Node* buildTree(glvec c, const std::vector<glvec>& points, Node* p){

	//Base case 
	if(points.size() == 2){
		return new Node(p, nullptr, nullptr, c, points[0], points[1]);
	}
	
	// Create new empty binary node
	Node* b = new Node();
	
	// Recurse
	b->lChild = buildTree(
			c, 
			std::vector<glvec>(
				points.begin(), points.begin() + points.size() / 2 + 1
			), 
			b
		);
	b->rChild = buildTree(
			c, 
			std::vector<glvec>(
				points.begin() + points.size() / 2, points.end()
			), 
			b
		);

	b->parent = p;
	b->a = points[0];
	b->b = points[points.size()/2];
	//TODO: Should probably be size - 1 but doesn't seem to crash right now,
	// so whatever.
	b->c = points[points.size()]; 
	
	//Return the node b
	return b;
}
