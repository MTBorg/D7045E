#include "triangulation.h"

#include <vector>
#include <iostream>

#include "util.h"
#include "binary_node.h"
#include "leaf_node.h"

Node* buildTree(glvec c, const std::vector<glvec>& points, Node* p){

	//Base case 
	if(points.size() == 2){
		return new LeafNode(p, c, points[0], points[1]);
	}
	
	// Create new empty binary node
	BinaryNode* b = new BinaryNode();
	
	// Recurse
	b->s1 = buildTree(
			c, 
			std::vector<glvec>(
				points.begin(), points.begin() + points.size() / 2 + 1
			), 
			b
		);
	b->s2 = buildTree(
			c, 
			std::vector<glvec>(
				points.begin() + points.size() / 2, points.end()
			), 
			b
		);

	b->parent = p;
	b->c = c;
	b->ci = points[0];
	b->cm = points[points.size()/2];
	b->cj = points[points.size() - 1]; 
	
	//Return the node b
	return b;
}


