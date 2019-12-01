#include <glm/vec2.hpp> // glm::vec3

#include "triangle.h"

class Node{
public:
	Node* parent = nullptr;
	Node* lChild = nullptr;
	Node* rChild = nullptr;
	glvec a, b, c;
	Node(): a(glvec(0,0)), b(glvec(0,0)), c(glvec(0,0)){}
	Node(Node* parent, Node* lChild, Node* rChild, glvec a, glvec b, glvec c):
		parent(parent),
		lChild(lChild),
		rChild(rChild), 
		a(a), b(b), c(c){}
};

class Leaf: public Node{
	Node* parent;
	Triangle t;
};
