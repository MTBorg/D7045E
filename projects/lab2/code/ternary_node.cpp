#include "ternary_node.h"

#include <vector>

#include "types.h"
#include "util.h"

TernaryNode::TernaryNode(
		Node* parent, Node* s1, Node* s2, Node* s3, glvec c, glvec ci, glvec cm, glvec cj):
Node(parent), s1(s1), s2(s2), s3(s3), c(c), ci(ci), cm(cm), cj(cj){}

std::vector<glvec> TernaryNode::toPointVec(){
	auto res = std::vector<glvec>();
	if(s1 != nullptr){
		auto points = s1->toPointVec();
		res.insert(res.end(), points.begin(), points.end());
	}
	if(s2 != nullptr){
		auto points = s2->toPointVec();
		res.insert(res.end(), points.begin(), points.end());
	}
	if(s3 != nullptr){
		auto points = s3->toPointVec();
		res.insert(res.end(), points.begin(), points.end());
	}

	return res;
}

Node* TernaryNode::insertPoint(const glvec& point){
	if(pointInSector(point, this->c, this->ci, this->cm)){
		s1 = s1->insertPoint(point);
	}else if(pointInSector(point, this->c, this->cm, this->cj)){
		s2 = s2->insertPoint(point);
	}else{
		s3 = s3->insertPoint(point);
	}
	return this;
}
