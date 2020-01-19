#ifndef GRAPHICS_NODE_H
#define GRAPHICS_NODE_H

#include <glm/glm.hpp>

#include "material.h"
#include "mesh.h"

class GraphicsNode {
private:
  Mesh *mesh;
  Material *material;
  glm::mat4 transform;

public:
  GraphicsNode(Mesh *mesh, Material *material, glm::mat4 transform)
      : mesh(mesh), material(material), transform(transform) {}
  void draw() const;
  inline void updateTransform(glm::mat4 transform) {
    this->transform = transform;
  }
};

#endif
