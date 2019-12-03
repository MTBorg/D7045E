#ifndef NODE_H
#define NODE_H
#include <glm/vec2.hpp> // glm::vec3

#include "types.h"

class Node{
public:
	Node* parent = nullptr;
	Node* s1 = nullptr;
	Node* s2 = nullptr;
	Node* s3 = nullptr;
	glvec c, ci, cm, cj;
	Node();
	Node(Node* parent, Node* s1, Node* s2, Node* s3, glvec c, glvec ci, glvec cm, glvec cj);
};

#endif
