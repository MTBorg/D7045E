#include "util.h"

#include "types.h"

#include <iostream>
#include <glm/glm.hpp>

int pickPointNotOnConvexHull(const std::vector<glvec>& points, const std::vector<glvec>& hull){
	for(auto it = points.begin(); it != points.end(); ++it){
		auto p = find(hull.begin(), hull.end(), *it);
		if(p == hull.end()){
			return it - points.begin();
		}
	}
	return -1;
}

bool pointInSector(const glvec& point, const glvec& c, const glvec& ci, const glvec& cm){
	if(pointLeftOfLine(cm, c, ci)){
		return !pointLeftOfLine(cm, c, point) || pointLeftOfLine(ci, c, point);
	}
	return pointLeftOfLine(ci, c, point) && !pointLeftOfLine(cm, c, point);
}

std::vector<glvec> removeDuplicates(std::vector<glvec> points){
	auto end = points.end();
	for(auto it = points.begin(); it != end; ++it){
		end = std::remove(it+1, end, *it);
	}
	points.erase(end, points.end());
	return points;
}

unsigned int getVertexIndexFromVertexBuffer(
		const glvec& vertex,
		const std::vector<GLfloat> vertexBuffer,
		const unsigned int bufferStride){
		for(
				auto it = vertexBuffer.begin();
				it <= vertexBuffer.end() - bufferStride;
				it+=bufferStride
			){
			if(*it == vertex.x && *(it+1) == vertex.y){
				return ((it - vertexBuffer.begin()) / bufferStride);
			}
		}
}

std::vector<glvec> generateRandomPoints(size_t size){
	auto res = std::vector<glvec>();
	srand(time(NULL));
	for(size_t i = 0; i < size; i++){
		int xSign = (rand() % 2) ? -1 : 1;
		int ySign = (rand() % 2) ? -1 : 1;
		res.emplace_back(
				xSign * (rand() % 10 / 10.f),
				ySign * (rand() % 10 / 10.f));
	}
	return res;
}
