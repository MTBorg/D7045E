#include "mesh.h"

Mesh::Mesh(const VertexVector& vertices){
	glGenBuffers(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(
		GL_ARRAY_BUFFER, 
		vertices.size() * sizeof(glm::vec3), 
		&vertices[0], 
		GL_STATIC_DRAW
	);
}

void Mesh::bindVAO(){
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glVertexAttribPointer(
		0,                  
		3,                  
		GL_FLOAT,           
		GL_FALSE,           
		0,                  
		(void*)0            
	);
}

void Mesh::unbindVAO(){
	glDisableVertexAttribArray(0);
}
