#include "node.h"
#include "types.h"

Node::Node(Node* parent, Node* lChild, Node* rChild, glvec a, glvec b, glvec c):
	parent(parent),
	lChild(lChild),
	rChild(rChild), 
	a(a), b(b), c(c){}

Node::Node(): a(glvec(0,0)), b(glvec(0,0)), c(glvec(0,0)){}
