#ifndef LEAF_NODE
#define LEAF_NODE

#include "node.h"

#include <vector>

class LeafNode: public Node{
public:
	glvec c, ci, cm;
	std::vector<glvec> toPointVec();
	Node* insertPoint(const glvec& point);
	LeafNode(Node* parent, glvec c, glvec ci, glvec cm)
		: Node(parent), c(c), ci(ci), cm(cm){}
};

#endif
