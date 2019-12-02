#ifndef NODE_H
#define NODE_H
#include <glm/vec2.hpp> // glm::vec3

#include "types.h"

class Node{
public:
	Node* parent = nullptr;
	Node* lChild = nullptr;
	Node* rChild = nullptr;
	glvec a, b, c;
	Node();
	Node(Node* parent, Node* lChild, Node* rChild, glvec a, glvec b, glvec c);
};

#endif
