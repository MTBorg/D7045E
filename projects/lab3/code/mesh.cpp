#include "mesh.h"

#include "types.h"

Mesh::Mesh(){
	setupVertexAttribPointers();
}

void Mesh::setupVertexAttribPointers(){
	glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(GlVec) + sizeof(Color),
			0
	);
	glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(GlVec) + sizeof(Color),
			(void*)(sizeof(GlVec) + sizeof(Color))
	);
}

void Mesh::loadVertices(const VertexVector& vertices){

}
