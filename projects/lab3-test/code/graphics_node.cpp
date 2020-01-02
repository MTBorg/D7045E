#include "graphics_node.h"

void GraphicsNode::draw(){
	mesh->bindVAO();
	material->applyMaterial();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	mesh->unbindVAO();
}
