#include "graphics_node.h"

void GraphicsNode::draw(){
	mesh->bindVAO();
	material->applyMaterial();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	mesh->unbindVAO();
}
