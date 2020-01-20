#ifndef CUBE_H
#define CUBE_H

#include "graphics_node.h"
#include "mesh.h"
#include "monochrome_material.h"
#include "types.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

GraphicsNode createCube(glm::vec3 position, RGBA color) {
  return GraphicsNode(
      new Mesh(VertexVector{
          Vertex(-0.5f, -0.5f, -0.5f), Vertex(0.5f, -0.5f, -0.5f),
          Vertex(0.5f, 0.5f, -0.5f),   Vertex(0.5f, 0.5f, -0.5f),
          Vertex(-0.5f, 0.5f, -0.5f),  Vertex(-0.5f, -0.5f, -0.5f),
          Vertex(-0.5f, -0.5f, 0.5f),  Vertex(0.5f, -0.5f, 0.5f),
          Vertex(0.5f, 0.5f, 0.5f),    Vertex(0.5f, 0.5f, 0.5f),
          Vertex(-0.5f, 0.5f, 0.5f),   Vertex(-0.5f, -0.5f, 0.5f),
          Vertex(-0.5f, 0.5f, 0.5f),   Vertex(-0.5f, 0.5f, -0.5f),
          Vertex(-0.5f, -0.5f, -0.5f), Vertex(-0.5f, -0.5f, -0.5f),
          Vertex(-0.5f, -0.5f, 0.5f),  Vertex(-0.5f, 0.5f, 0.5f),
          Vertex(0.5f, 0.5f, 0.5f),    Vertex(0.5f, 0.5f, -0.5f),
          Vertex(0.5f, -0.5f, -0.5f),  Vertex(0.5f, -0.5f, -0.5f),
          Vertex(0.5f, -0.5f, 0.5f),   Vertex(0.5f, 0.5f, 0.5f),
          Vertex(-0.5f, -0.5f, -0.5f), Vertex(0.5f, -0.5f, -0.5f),
          Vertex(0.5f, -0.5f, 0.5f),   Vertex(0.5f, -0.5f, 0.5f),
          Vertex(-0.5f, -0.5f, 0.5f),  Vertex(-0.5f, -0.5f, -0.5f),
          Vertex(-0.5f, 0.5f, -0.5f),  Vertex(0.5f, 0.5f, -0.5f),
          Vertex(0.5f, 0.5f, 0.5f),    Vertex(0.5f, 0.5f, 0.5f),
          Vertex(-0.5f, 0.5f, 0.5f),   Vertex(-0.5f, 0.5f, -0.5f)}),
      new MonochromeMaterial(color), glm::translate(glm::mat4(1.0f), position));
}

#endif
