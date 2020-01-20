#include "graphics_node.h"

void GraphicsNode::draw() const {
  mesh->bindVAO();
  material->applyMaterial(transform);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  mesh->unbindVAO();
}
