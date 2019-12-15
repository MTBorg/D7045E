#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2017 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
class Lab3App : public Core::App
{
public:
	/// constructor
	Lab3App();
	/// destructor
	~Lab3App();

	bool Open();
	void Run();

	Display::Window* window;
};
