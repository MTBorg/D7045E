#ifndef GRAPHICSNODE_H
#define GRAPHICSNODE_H

#include "mesh.h"
#include "material.h"
#include <glm/glm.hpp>

class GraphicsNode{
private:
	Mesh* mesh;
	Material* material;
	glm::mat4 transform;
public:
	GraphicsNode(
			Mesh * mesh,
			Material* material,
			glm::mat4 transform
	): mesh(mesh), material(material), transform(transform){}
	void draw();
};

#endif
