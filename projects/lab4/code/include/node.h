#ifndef NODE_H
#define NODE_H

#define GLM_ENABLE_EXPERIMENTAL // Enable gtx import
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp> //needed for scaling apparently

class Node {
protected:
  glm::mat4 transform;

public:
  Node(glm::mat4 transform) : transform(transform) {}

  virtual void update() {}
  inline glm::mat4 getTransform() const { return transform; }

  inline void translate(glm::vec3 direction) {
    transform = glm::translate(transform, direction);
  }

  inline void translateGlobal(glm::vec3 direction) {
    transform[3][0] += direction.x;
    transform[3][1] += direction.y;
    transform[3][2] += direction.z;
  }

  inline void rotate(glm::vec3 axis, float angle) {
    transform = glm::rotate(transform, glm::radians(angle), axis);
  }

  inline void scale(float x, float y, float z) {
    transform = transform * glm::scale(glm::vec3(x, y, z));
  }
};

#endif
