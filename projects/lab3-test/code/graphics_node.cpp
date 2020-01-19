#include "graphics_node.h"

void GraphicsNode::draw() {
  mesh->bindVAO();
  material->applyMaterial(transform);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  mesh->unbindVAO();
}
