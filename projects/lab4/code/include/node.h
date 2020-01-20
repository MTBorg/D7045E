#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Node {
protected:
  glm::mat4 transform;

public:
  Node(glm::mat4 transform) : transform(transform) {}

  virtual void update() {}
  inline glm::mat4 getTransform() const { return transform; }
};

#endif
