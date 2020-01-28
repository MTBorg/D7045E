#pragma once
//------------------------------------------------------------------------------
/**
        Application class used for example application.

        (C) 2015-2017 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "camera.h"
#include "config.h"
#include "core/app.h"
#include "render/window.h"
#include "scene.h"
#include <glm/vec3.hpp>

class Lab4 : public Core::App {
public:
  Lab4();
  ~Lab4();

  bool Open();
  void Run();
  void initObjects();

private:
  Display::Window *window;
  Scene scene =
      Scene(Camera(glm::translate(glm::mat4(1), glm::vec3(0, 7, 4))),
            LightSource(glm::translate(glm::mat4(1), glm::vec3(0, 0, 4)),
                        RGB(1, 1, 1), 0.1));
};
