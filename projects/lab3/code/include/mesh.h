#ifndef MESH_H
#define MESH_H

#include "types.h"
#include <GL/glew.h>

class Mesh{
private:
	GLuint vao, vbo, ibo;
	void setupVertexAttribPointers();
	VertexVector vertices;
public:
	Mesh(const VertexVector& vertices);
	void bindVertexArrayObject();
	void unbindVertexArrayObject();
	inline const VertexVector& getVertices() const{return vertices;};
};

#endif
