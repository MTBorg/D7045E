#ifndef GRAPHICS_NODE_H
#define GRAPHICS_NODE_H

#include <glm/glm.hpp>
/* #include <glm/gtc/matrix_transform.hpp> */
#include <glm/vec3.hpp>
#include <vector>

#include "node.h"

#include "light_source.h"
#include "material.h"
#include "mesh.h"

#include <iostream>

class GraphicsNode : public Node {
private:
  Mesh *mesh;
  Material *material;
  std::vector<glm::mat4> transformUpdates;
  std::vector<GraphicsNode *> children;
  void (*animation)(glm::mat4 *transform) = nullptr;

public:
  GraphicsNode(
      Mesh *mesh, Material *material, glm::mat4 transform,
      std::vector<GraphicsNode *> children = std::vector<GraphicsNode *>())
      : Node(transform), mesh(mesh), material(material), children(children) {}
  void draw(const glm::mat4 &view, const LightSource &lightSource,
            const glm::mat4 *const parentTransform = nullptr) const;
  void update() override {

    // Apply the matrix transforms
    auto result = transform;
    for (const auto &update : transformUpdates) {
      result *= update;
    }
    transform = result;

    if (animation != nullptr) {
      animation(&transform);
    }

    transformUpdates.clear();

    for (auto &child : children) {
      child->update();
    }
  }

  inline void addTransformUpdate(glm::mat4 update) {
    transformUpdates.push_back(update);
  }
  inline void setAnimation(void (*animation)(glm::mat4 *)) {
    this->animation = animation;
  }
};

#endif
