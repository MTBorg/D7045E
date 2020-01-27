#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "camera.h"
#include "graphics_node.h"
#include "light_source.h"

class Scene {
public:
  std::vector<GraphicsNode> objectsMovable;
  Camera camera;
  LightSource lightSource;

  void render();

  Scene(Camera camera, LightSource lightSource)
      : camera(camera), lightSource(lightSource) {}
};

#endif
