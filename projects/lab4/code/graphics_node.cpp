#include "graphics_node.h"

void GraphicsNode::draw(const glm::mat4 &view,
                        const LightSource &lightSource) const {
  mesh->bindVAO();
  material->applyMaterial(getTransform(), view, lightSource);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  mesh->unbindVAO();
}
