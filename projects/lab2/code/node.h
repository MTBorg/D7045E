#ifndef NODE_H
#define NODE_H
#include <glm/vec2.hpp> // glm::vec3
#include <vector>

#include "types.h"

class Node{
public:
	glvec c, ci, cm, cj;
	Node* parent = nullptr;

	virtual std::vector<glvec> toPointVec() = 0;
	virtual void insertPoint(const glvec& point) = 0;
	virtual bool containsPoint(const glvec& point) = 0;
	/* virtual Node* buildTree() = 0; */
	Node(){}
	Node(Node* parent):parent(parent){}
};

class BinaryNode: public Node{
public:
	Node* s1 = nullptr;
	Node* s2 = nullptr;
	glvec c, ci, cm, cj;

	BinaryNode(Node* parent, Node* s1, Node* s2, glvec c, glvec ci, glvec cm, glvec cj);
	BinaryNode(){};
	std::vector<glvec> toPointVec();
	void insertPoint(const glvec& point);
	bool containsPoint(const glvec& point);
	/* Node* buildTree(); */
};

class TernaryNode: public Node{
public:
	Node* s1 = nullptr;
	Node* s2 = nullptr;
	Node* s3 = nullptr;
	glvec c, ci, cm, cj;

	virtual std::vector<glvec> toPointVec();
	void insertPoint(const glvec& point);
	bool containsPoint(const glvec& point);
};

class LeafNode: public Node{
public:
	glvec c, ci1, ci2;
	std::vector<glvec> toPointVec();
	void insertPoint(const glvec& point);
	/* Node* buildTree(); */
	LeafNode(Node* parent, glvec c,glvec ci1,glvec ci2)
		: Node(parent), c(c), ci1(ci1), ci2(ci2){}
	bool containsPoint(const glvec& point);
};

#endif
