//------------------------------------------------------------------------------
// lab2.cpp
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "lab3.h"
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <map>

//DEBUG
#include "material.h"
#include "mesh.h"
#include "simple_material.h"
#include "graphics_node.h"
#include "shader.h"
///

const GLchar* vs =
"#version 310 es\n"
"precision mediump float;\n"
"layout(location=0) in vec2 pos;\n"
"layout(location=1) in vec4 color;\n"
"layout(location=0) out vec4 Color;\n"
"uniform float angle;\n"
"void main()\n"
"{\n"
" float offset = 10.f * float(gl_VertexID);\n"
" float x = pos[0] + 0.05f * cos(angle + offset) / 4.f;\n"
" float y = pos[1] + 0.05f * sin(angle + offset) / 4.f;\n"
"	gl_Position = vec4(x, y, -1, 1);\n"
" Color = color;\n"
"}\n";

const GLchar* ps =
"#version 310 es\n"
"precision mediump float;\n"
"layout(location=0) in vec4 color;\n"
"out vec4 Color;\n"
"void main()\n"
"{\n"
"	Color = color;\n"
"}\n";

using namespace Display;

Lab3App::Lab3App(){} 
Lab3App::~Lab3App(){} 

bool Lab3App::Open(){
	/* printf("generating points...\n"); */

	/* generateRandomTriangulationSet(5); */

	App::Open();
	this->window = new Display::Window;
	this->window->SetSize(500,500);
	window->SetKeyPressFunction([this](int32 keyCode, int32, int32 action, int32)
	{
		if(keyCode == GLFW_KEY_ESCAPE){
			this->window->Close();
		}
	});

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(1, 1,1,1);
		return true;
	}
	return false;
}

void Lab3App::Run(){
	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();

		this->window->SwapBuffers();
	}
}
