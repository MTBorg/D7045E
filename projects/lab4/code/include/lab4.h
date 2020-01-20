#pragma once
//------------------------------------------------------------------------------
/**
        Application class used for example application.

        (C) 2015-2017 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "config.h"
#include "core/app.h"
#include "render/window.h"
#include "scene.h"

class Lab4 : public Core::App {
public:
  Lab4();
  ~Lab4();

  bool Open();
  void Run();
  void initObjects();

private:
  Display::Window *window;
  Scene scene;
};
