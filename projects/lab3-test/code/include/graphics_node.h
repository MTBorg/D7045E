#ifndef GRAPHICS_NODE_H
#define GRAPHICS_NODE_H

#include "mesh.h"
#include "material.h"

class GraphicsNode{
private:
	Mesh* mesh;
	Material* material;
public:
	GraphicsNode(Mesh* mesh, Material* material): mesh(mesh), material(material){}
	void draw();
};

#endif
