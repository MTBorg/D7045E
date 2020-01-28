#include "graphics_node.h"

#include <iostream>

void GraphicsNode::draw(const glm::mat4 &view, const LightSource &lightSource,
                        const glm::mat4 *const parentTransform) const {
  mesh->bindVAO();

  // Move child to parent
  auto drawTransform = transform;
  if (parentTransform != nullptr) {
    auto pTransform = *parentTransform;

    // Move the mesh to the parents location
    drawTransform = glm::translate(
        glm::mat4(1),
        glm::vec3(pTransform[3][0], pTransform[3][1], pTransform[3][2]));

    // Rotate according to parent
    auto rotationMatrix = glm::mat4(
        pTransform[0][0], pTransform[0][1], pTransform[0][2], 0, // column 1
        pTransform[1][0], pTransform[1][1], pTransform[1][2], 0, // column 2
        pTransform[2][0], pTransform[2][1], pTransform[2][2], 0, // column 3
        0, 0, 0, 1);
    drawTransform *= rotationMatrix;

    // Move back to it's own position
    drawTransform = glm::translate(
        drawTransform,
        glm::vec3(transform[3][0], transform[3][1], transform[3][2]));

    // Rotate according to it's own transform
    rotationMatrix = glm::mat4(
        transform[0][0], transform[0][1], transform[0][2], 0, // column 1
        transform[1][0], transform[1][1], transform[1][2], 0, // column 2
        transform[2][0], transform[2][1], transform[2][2], 0, // column 3
        0, 0, 0, 1);
    drawTransform *= rotationMatrix;
  }
  material->applyMaterial(drawTransform, view, lightSource);

  glDrawArrays(GL_TRIANGLES, 0, 36);
  mesh->unbindVAO();

  for (auto &child : children) {
    child->draw(view, lightSource, &drawTransform);
  }
}
