#ifndef GRAPHICS_NODE_H
#define GRAPHICS_NODE_H

#include <glm/glm.hpp>
/* #include <glm/gtc/matrix_transform.hpp> */
#include <glm/vec3.hpp>
#include <vector>

#include "node.h"

#include "material.h"
#include "mesh.h"

#include <iostream>

class GraphicsNode : public Node {
private:
  Mesh *mesh;
  Material *material;
  std::vector<glm::mat4> transformUpdates;
  void (*animation)(glm::mat4 *transform) = nullptr;

public:
  GraphicsNode(Mesh *mesh, Material *material, glm::mat4 transform)
      : Node(transform), mesh(mesh), material(material) {}
  void draw() const;
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
  }

  inline void addTransformUpdate(glm::mat4 update) {
    transformUpdates.push_back(update);
  }
  inline void setAnimation(void (*animation)(glm::mat4 *)) {
    this->animation = animation;
  }
};

#endif
