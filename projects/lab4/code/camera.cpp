#include "camera.h"

#include <glm/glm.hpp>

glm::mat4 Camera::getViewMatrix() {
  auto lookAt = glm::vec3(0, 0, -1);
  auto translated = glm::translate(transform, lookAt);
  lookAt =
      glm::mat3(transform[0][0], transform[1][0], transform[2][0], // column 1
                transform[0][1], transform[1][1], transform[2][1], // column 2
                transform[0][2], transform[1][2], transform[2][2]) // column 3
      * lookAt;
  lookAt = glm::vec3(translated[3][0], translated[3][1], translated[3][2]);
  return glm::lookAt(
      glm::vec3(transform[3][0], transform[3][1], transform[3][2]), lookAt,
      glm::vec3(0, 1, 0));
}
