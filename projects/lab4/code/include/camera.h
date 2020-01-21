#ifndef CAMERA_H
#define CAMERA_H

#include "node.h"

#include <glm/glm.hpp>

class Camera : public Node {
private:
  glm::mat4 projectionMatrix;

public:
  Camera(glm::mat4 transform) : Node(transform) {}

  glm::mat4 getViewMatrix();
};

#endif
