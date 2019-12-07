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
	if(pointOnLine(point, this->c, this->ci)){
		s1 = s1->insertPoint(point);
		//The root should always update both subtrees
		if(this->isRoot()) s2 = s2->insertPoint(point); 
	} else if(pointOnLine(point, c, cm)){
		s1 = s1->insertPoint(point);
		s2 = s2->insertPoint(point);
	}else if(pointOnLine(point, c, cj)){
		s2 = s2->insertPoint(point);
		//The root should always update both subtrees
		if(this->isRoot()) s1 = s1->insertPoint(point);
	}else if(pointOnLine(point, ci, cm)){
		s1 = s1->insertPoint(point);
	}else if(pointOnLine(point, cm, cj)){
		s2 = s2->insertPoint(point);
	} else if(pointInSector(point, c, ci, cm)){
		s1 = s1->insertPoint(point);
	}else if(pointInSector(point, c, cm, cj)){
		s2 = s2->insertPoint(point);
	}else{
		printf("POINT NOT FOUND: THIS SHOULD NEVER BE REACHED\n");
	}
	return this;
}
