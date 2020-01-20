#ifndef GRAPHICS_NODE_H
#define GRAPHICS_NODE_H

#include <glm/glm.hpp>
/* #include <glm/gtc/matrix_transform.hpp> */
#include <glm/vec3.hpp>

#include "node.h"

#include "material.h"
#include "mesh.h"

class GraphicsNode : public Node {
private:
  Mesh *mesh;
  Material *material;
  /* glm::mat4 transform; */

public:
  GraphicsNode(Mesh *mesh, Material *material, glm::mat4 transform)
      : Node(transform), mesh(mesh), material(material) {}
  void draw() const;
};

#endif
