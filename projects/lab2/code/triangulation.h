#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>

#include "node.h"
#include "types.h"

Node* buildTree(glvec c, const std::vector<glvec>& points, Node* p);
void insertPointIntoTree(const glvec& point, Node* tree);

#endif
