#ifndef LIGHT_SOURCE
#define LIGHT_SOURCE

#include "node.h"

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
};

#endif
