#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>

#include "types.h"

class Mesh{
private:
	GLuint vao;
public:
	Mesh(const VertexVector& vertices);

	void bindVAO();
	void unbindVAO();

	static Mesh* createCuboid();
};

#endif
