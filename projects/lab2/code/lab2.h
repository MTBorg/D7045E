#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2017 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
class Lab2App : public Core::App
{
public:
	/// constructor
	Lab2App();
	/// destructor
	~Lab2App();

	/// open app
	bool Open();
	/// run app
	void Run();

	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;
	GLuint triangle;
	GLuint ibo;
	Display::Window* window;
};
