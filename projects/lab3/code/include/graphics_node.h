#ifndef GRAPHICS_NODE_H
#define GRAPHICS_NODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

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
  inline void translate(glm::vec3 m) {
    transform = glm::translate(transform, m);
  }
  inline void rotate(float degrees, glm::vec3 axis) {
    transform = glm::rotate(transform, glm::radians(degrees), axis);
  }
};

#endif
