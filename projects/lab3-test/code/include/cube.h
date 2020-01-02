#ifndef CUBE_H
#define CUBE_H

#include "graphics_node.h"
#include "mesh.h"
#include "types.h"

GraphicsNode createCube(){
	return GraphicsNode(
		new Mesh(
			VertexVector{
		 Vertex(-0.5f, -0.5f, -0.5f),
     Vertex(0.5f, -0.5f, -0.5f),
     Vertex(0.5f,  0.5f, -0.5f),
     Vertex(0.5f,  0.5f, -0.5f),
    Vertex(-0.5f,  0.5f, -0.5f),
    Vertex(-0.5f, -0.5f, -0.5f),
    Vertex(-0.5f, -0.5f,  0.5f),
     Vertex(0.5f, -0.5f,  0.5f),
     Vertex(0.5f,  0.5f,  0.5f),
     Vertex(0.5f,  0.5f,  0.5f),
    Vertex(-0.5f,  0.5f,  0.5f),
    Vertex(-0.5f, -0.5f,  0.5f),
    Vertex(-0.5f,  0.5f,  0.5f),
    Vertex(-0.5f,  0.5f, -0.5f),
    Vertex(-0.5f, -0.5f, -0.5f),
    Vertex(-0.5f, -0.5f, -0.5f),
    Vertex(-0.5f, -0.5f,  0.5f),
    Vertex(-0.5f,  0.5f,  0.5f),
     Vertex(0.5f,  0.5f,  0.5f),
     Vertex(0.5f,  0.5f, -0.5f),
     Vertex(0.5f, -0.5f, -0.5f),
     Vertex(0.5f, -0.5f, -0.5f),
     Vertex(0.5f, -0.5f,  0.5f),
     Vertex(0.5f,  0.5f,  0.5f),
    Vertex(-0.5f, -0.5f, -0.5f),
     Vertex(0.5f, -0.5f, -0.5f),
     Vertex(0.5f, -0.5f,  0.5f),
     Vertex(0.5f, -0.5f,  0.5f),
    Vertex(-0.5f, -0.5f,  0.5f),
    Vertex(-0.5f, -0.5f, -0.5f),
    Vertex(-0.5f,  0.5f, -0.5f),
     Vertex(0.5f,  0.5f, -0.5f),
     Vertex(0.5f,  0.5f,  0.5f),
     Vertex(0.5f,  0.5f,  0.5f),
    Vertex(-0.5f,  0.5f,  0.5f),
    Vertex(-0.5f,  0.5f, -0.5f)}
		),
		new MonochromeMaterial(RGBA(1,0,0,1))
	);
}

#endif
