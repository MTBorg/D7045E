#include "leaf_node.h"

#include "types.h"
#include "node.h"
#include "binary_node.h"
#include "ternary_node.h"
#include "util.h"

#include <iostream>

std::vector<glvec> LeafNode::toPointVec(){
	return {c, ci, cm};
}

Node* LeafNode::insertPoint(const glvec& point){
	if(pointOnLine(this->c, this->ci, point)){ // On c->ci
		BinaryNode* b = new BinaryNode();
		b->parent = this->parent;
		b->s1 = new LeafNode(b, point, this->ci, this->cm);
		b->s2 = new LeafNode(b, point, this->cm, this->c);
		b->c = point;
		b->ci = this->ci;
		b->cm = this->cm;
		b->cj = this->c;
		return b;
	}else if(pointOnLine(this->c, this->cm, point)){ // On c->cm
		BinaryNode* b = new BinaryNode();
		b->parent = this->parent;
		b->s1 = new LeafNode(b, point, this->c, this->ci);
		b->s2 = new LeafNode(b, point, this->ci, this->cm);
		b->c = point;
		b->ci = this->c;
		b->cm = this->ci;
		b->cj = this->cm;
		return b;
	}else if(pointOnLine(this->ci, this->cm, point)){ // On ci->cm
		BinaryNode* b = new BinaryNode();
		b->parent = this->parent;
		b->s1 = new LeafNode(b, point, this->c, this->ci);
		b->s2 = new LeafNode(b, point, this->ci, this->cm);
		b->c = point;
		b->ci = this->cm;
		b->cm = this->c;
		b->cj = this->ci;
		return b;
	}else{ //Inside the triangle
		TernaryNode *t = new TernaryNode(
				this->parent, nullptr, nullptr, nullptr, point, this->ci, this->cm, this->c);
		t->s1 = new LeafNode(t, point, this->ci, this->cm);
		t->s2 = new LeafNode(t, point, this->cm, this->c);
		t->s3 = new LeafNode(t, point, this->c, this->ci);

		return t;
	}
}
