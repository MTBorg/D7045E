#include "graphics_node.h"
#include <iostream>

void GraphicsNode::draw(){
	printf("AWIDIAUWDHiUAWHD");
	mesh->bindVertexArrayObject();
	material->applyMaterial();

	glDrawArrays(GL_TRIANGLES, 0, mesh->getVertices().size()/3);
}
