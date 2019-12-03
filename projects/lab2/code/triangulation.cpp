#include "triangulation.h"

#include <vector>
#include <iostream>

#include "util.h"

Node* buildTree(glvec c, const std::vector<glvec>& points, Node* p){

	//Base case 
	if(points.size() == 2){
		return new Node(p, nullptr, nullptr, nullptr, c, c, points[0], points[1]);
	}
	
	// Create new empty binary node
	Node* b = new Node();
	
	// Recurse
	b->s1 = buildTree(
			c, 
			std::vector<glvec>(
				points.begin(), points.begin() + points.size() / 2 + 1
			), 
			b
		);
	b->s2 = buildTree(
			c, 
			std::vector<glvec>(
				points.begin() + points.size() / 2, points.end()
			), 
			b
		);
	b->s3 = nullptr;

	b->parent = p;
	b->c = c;
	b->ci = points[0];
	b->cm = points[points.size()/2];
	b->cj = points[points.size() - 1]; 
	
	//Return the node b
	return b;
}

bool pointIsInSector(const glvec& point, const Node* sector){
	bool case1 =
	!pointLeftOfLine(sector->c, sector->cm, sector->ci) && (
			(
				//Between cm->c and ci->c
				pointLeftOfLine(sector->ci, sector->c, point) ||
				!pointLeftOfLine(sector->cm, sector->c, point)
			) ||
			(
				//Between cm->c and cj->c
				pointLeftOfLine(sector->cm, sector->c, point) &&
			 !pointLeftOfLine(sector->cj, sector->c, point)
			) 
	);

	bool case2 = 
	pointLeftOfLine(sector->c, sector->cm, sector->ci) && (
		 	//Between cm->c and cj->c
			(pointLeftOfLine(sector->cm, sector->c, point) &&
			!pointLeftOfLine(sector->cj, sector->c, point)
			) ||
			(
				// Between ci->c and cm->c
				pointLeftOfLine(sector->ci, sector->c, point) &&
			 	!pointLeftOfLine(sector->cm, sector->c, point)
			)
		);

	return case1 || case2;
}

void insertPointIntoTree(const glvec& point, Node* root){
	// Base case
	if(root->s1 == nullptr && root->s2 == nullptr && root->s3 == nullptr){
		root->s1 = new Node(
				root, nullptr, nullptr, nullptr, point, point, root->ci, root->cm
		);
		root->s2 = new Node(
				root, nullptr, nullptr, nullptr, point, point, root->cm, root->cj
		);
		root->s3 = new Node(
				root, nullptr, nullptr, nullptr, point, point, root->cj, root->ci
		);
		return;
	}

	if(root->s1 != nullptr){
		if (pointIsInSector(point, root->s1)){
			insertPointIntoTree(point, root->s1);
			return;
		}
	}
	if(root->s2 != nullptr){
		if (pointIsInSector(point, root->s2)){
			insertPointIntoTree(point, root->s2);
			return;
		}
	}

	if(root->s3 != nullptr){
		if (pointIsInSector(point, root->s3)){
			insertPointIntoTree(point, root->s3);
			return;
		}
	}

	printf("THIS SHOULD NOT BE REACHED\n");
}
