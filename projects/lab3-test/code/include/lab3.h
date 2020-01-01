#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2017 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
class Lab3 : public Core::App
{
public:
	Lab3();
	~Lab3();

	bool Open();
	void Run();
private:
	Display::Window* window;
};
