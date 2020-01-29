#ifndef LIGHT_SOURCE
#define LIGHT_SOURCE

#include "node.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "types.h"

class LightSource : public Node {
private:
  RGB color;
  float intensity;

public:
  LightSource(glm::mat4 transform, RGB color, float intensity)
      : Node(transform), color(color), intensity(intensity) {}

  inline RGB getColor() const { return color; }
  inline float getIntensity() const { return intensity; }

  inline void translate(glm::vec3 direction) {
    transform = glm::translate(transform, direction);
  }
};

#endif
