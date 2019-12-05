#include "leaf_node.h"

#include "types.h"
#include "node.h"
#include "ternary_node.h"

std::vector<glvec> LeafNode::toPointVec(){
	return {c, ci, cm};
}

Node* LeafNode::insertPoint(const glvec& point){
	TernaryNode *t = new TernaryNode(
			this->parent, nullptr, nullptr, nullptr, point, this->ci, this->cm, this->c);
	t->s1 = new LeafNode(t, point, this->ci, this->cm);
	t->s2 = new LeafNode(t, point, this->cm, this->c);
	t->s3 = new LeafNode(t, point, this->c, this->ci);

	return t;
}
