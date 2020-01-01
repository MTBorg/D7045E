#include "mesh.h"

#include "types.h"
#include <GL/glew.h>
#include <iostream>

Mesh::Mesh(const VertexVector& vertices){
	printf("Mesh constructor");
	this->vertices = vertices;
	
	return;
	//Generate buffers
	glGenBuffers(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
}

void Mesh::setupVertexAttribPointers(){
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
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

void Mesh::bindVertexArrayObject(){
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(
			GL_ARRAY_BUFFER,
			vertices.size() * sizeof(GLfloat),
			&vertices[0],
			GL_STATIC_DRAW
	);

	setupVertexAttribPointers();
}

void Mesh::unbindVertexArrayObject(){

}
