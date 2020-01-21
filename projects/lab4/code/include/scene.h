#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "camera.h"
#include "graphics_node.h"

class Scene {
public:
  std::vector<GraphicsNode> objectsMovable;
  void render();
  Camera camera;

  Scene(Camera camera) : camera(camera) {}
};

#endif
