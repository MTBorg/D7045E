#include "node.h"
#include "types.h"

Node::Node(Node* parent, Node* s1, Node* s2, Node* s3, glvec c, glvec ci, glvec cm, glvec cj):
	parent(parent),
	s1(s1),
	s2(s2), 
	s3(s3),
	c(c),
	ci(ci),
	cm(cm),
	cj(cj)
	{}

Node::Node(){}
