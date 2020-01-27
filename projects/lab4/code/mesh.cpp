#include "mesh.h"

#include <iostream>

Mesh::Mesh(const VertexVector &vertices, const NormalVector &normals) {
  glGenBuffers(1, &vao);
  glBindBuffer(GL_ARRAY_BUFFER, vao);

  // This is so ugly it makes me chronically sad
  auto temp = std::vector<glm::vec3>();
  for (auto i = 0; i < vertices.size(); i++) {
    temp.push_back(vertices[i]);
    temp.push_back(normals[i]);
  }

  glBufferData(GL_ARRAY_BUFFER, temp.size() * sizeof(glm::vec3) * 2, &temp[0],
               GL_STATIC_DRAW);
}

void Mesh::bindVAO() {
  glBindBuffer(GL_ARRAY_BUFFER, vao);

  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void Mesh::unbindVAO() { glDisableVertexAttribArray(0); }

Mesh *Mesh::createCuboid() {
  return new Mesh(
      VertexVector{Vertex(-0.5f, -0.5f, -0.5f), Vertex(0.5f, -0.5f, -0.5f),
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
                   Vertex(-0.5f, 0.5f, 0.5f),   Vertex(-0.5f, 0.5f, -0.5f)},
      NormalVector{
          Normal(0.0f, 0.0f, -1.0f), Normal(0.0f, 0.0f, -1.0f),
          Normal(0.0f, 0.0f, -1.0f), Normal(0.0f, 0.0f, -1.0f),
          Normal(0.0f, 0.0f, -1.0f), Normal(0.0f, 0.0f, -1.0f),

          Normal(0.0f, 0.0f, 1.0f),  Normal(0.0f, 0.0f, 1.0f),
          Normal(0.0f, 0.0f, 1.0f),  Normal(0.0f, 0.0f, 1.0f),
          Normal(0.0f, 0.0f, 1.0f),  Normal(0.0f, 0.0f, 1.0f),

          Normal(1.0f, 0.0f, 0.0f),  Normal(1.0f, 0.0f, 0.0f),
          Normal(1.0f, 0.0f, 0.0f),  Normal(1.0f, 0.0f, 0.0f),
          Normal(1.0f, 0.0f, 0.0f),  Normal(1.0f, 0.0f, 0.0f),

          Normal(1.0f, 0.0f, 0.0f),  Normal(1.0f, 0.0f, 0.0f),
          Normal(1.0f, 0.0f, 0.0f),  Normal(1.0f, 0.0f, 0.0f),
          Normal(1.0f, 0.0f, 0.0f),  Normal(1.0f, 0.0f, 0.0f),

          Normal(0.0f, -1.0f, 0.0f), Normal(0.0f, -1.0f, 0.0f),
          Normal(0.0f, -1.0f, 0.0f), Normal(0.0f, -1.0f, 0.0f),
          Normal(0.0f, -1.0f, 0.0f), Normal(0.0f, -1.0f, 0.0f),

          Normal(0.0f, 1.0f, 0.0f),  Normal(0.0f, 1.0f, 0.0f),
          Normal(0.0f, 1.0f, 0.0f),  Normal(0.0f, 1.0f, 0.0f),
          Normal(0.0f, 1.0f, 0.0f),  Normal(0.0f, 1.0f, 0.0),

      });
}
