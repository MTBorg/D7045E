#ifndef TERNARY_NODE_H
#define TERNARY_NODE_H

#include "node.h"

#include <vector>

class TernaryNode: public Node{
public:
	Node* s1 = nullptr;
	Node* s2 = nullptr;
	Node* s3 = nullptr;
	glvec c, ci, cm, cj;

	virtual std::vector<glvec> toPointVec();
	Node* insertPoint(const glvec& point);
	TernaryNode(Node* parent, Node* s1, Node* s2, Node* s3, glvec c, glvec ci, glvec cm, glvec cj);
};

#endif
