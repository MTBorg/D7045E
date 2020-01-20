#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Node {
private:
  glm::mat4 transform;

protected:
  inline glm::mat4 getTransform() const { return transform; }

public:
  Node(glm::mat4 transform) : transform(transform) {}

  virtual void update() {}
  inline void translate(glm::vec3 m) {
    transform = glm::translate(transform, m);
  }
  inline void rotate(float degrees, glm::vec3 axis) {
    transform = glm::rotate(transform, glm::radians(degrees), axis);
  }
};

#endif
