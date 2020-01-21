#include "graphics_node.h"

void GraphicsNode::draw(const glm::mat4 &view) const {
  mesh->bindVAO();
  material->applyMaterial(getTransform(), view);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  mesh->unbindVAO();
}
