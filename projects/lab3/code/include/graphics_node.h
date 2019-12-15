#ifndef GRAPHICSNODE_H
#define GRAPHICSNODE_H

#include "mesh.h"
#include "material.h"
#include <glm/glm.hpp>

class GraphicsNode{
private:
	Mesh* mesh;
	Material* material;
	glm::mat4 tranform;
public:
	void Draw();
};

#endif
