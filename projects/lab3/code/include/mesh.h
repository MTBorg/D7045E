#ifndef MESH_H
#define MESH_H

#include "types.h"
#include <GL/glew.h>

class Mesh{
private:
	GLuint vao, vbo, ibo;
	void setupVertexAttribPointers();
public:
	Mesh();
	void loadVertices(const VertexVector& vertices);
};

#endif
