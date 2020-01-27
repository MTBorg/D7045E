#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>

#include "types.h"

class Mesh {
private:
  GLuint vao;

public:
  Mesh(const VertexVector &vertices, const NormalVector &normals);

  void bindVAO();
  void unbindVAO();

  static Mesh *createCuboid();
};

#endif
