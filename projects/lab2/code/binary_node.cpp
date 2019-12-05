#include "binary_node.h"

#include "node.h"
#include "binary_node.h"
#include "util.h"
#include "types.h"

#include <vector>
#include <iostream>

BinaryNode::BinaryNode(Node* parent, Node* s1, Node* s2, glvec c, glvec ci, glvec cm, glvec cj):
Node(parent), s1(s1), s2(s2), c(c), ci(ci), cm(cm), cj(cj){}

std::vector<glvec> BinaryNode::toPointVec(){
	auto res = std::vector<glvec>();
	if(s1 != nullptr){
		auto points = s1->toPointVec();
		res.insert(res.end(), points.begin(), points.end());
	}
	if(s2 != nullptr){
		auto points = s2->toPointVec();
		res.insert(res.end(), points.begin(), points.end());
	}

	return res;
}

Node* BinaryNode::insertPoint(const glvec& point){
	if(pointInSector(point, this->c, this->ci, this->cm)){
		this->s1 = this->s1->insertPoint(point);
	}else if(pointInSector(point, this->c, this->cm, this->cj)){
		this->s2 = this->s2->insertPoint(point);
	}else{
		printf("THIS SHOULD NEVER BE REACHED\n");
	}
	return this;
}
