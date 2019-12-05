#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include "node.h"

#include <vector>

class BinaryNode: public Node{
public:
	Node* s1 = nullptr;
	Node* s2 = nullptr;
	glvec c, ci, cm, cj;

	BinaryNode(Node* parent, Node* s1, Node* s2, glvec c, glvec ci, glvec cm, glvec cj);
	BinaryNode(){};
	std::vector<glvec> toPointVec();
	Node* insertPoint(const glvec& point);
};

#endif
