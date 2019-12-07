#ifndef NODE_H
#define NODE_H
#include <glm/vec2.hpp> // glm::vec3
#include <vector>

#include "types.h"

class Node{
public:
	Node* parent = nullptr;

	virtual std::vector<glvec> toPointVec() = 0;
	virtual Node* insertPoint(const glvec& point) = 0;
	inline bool isRoot(){return parent == nullptr;}

	Node(){}
	Node(Node* parent):parent(parent){}
};

#endif
