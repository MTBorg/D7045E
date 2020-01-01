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

using namespace Display;

Lab3App::Lab3App(){} 
Lab3App::~Lab3App(){} 

Mesh triangle = Mesh(
	VertexVector(
		/* { */
		/* 	GlVec(0, 0.5f, 0), */
		/* 	GlVec(-0.5f, 0, 0), */
		/* 	GlVec(0.5f, 0, 0) */
		/* } */
	)
);

/* const std::vector<GraphicsNode> objects = { */
/* 	GraphicsNode( */
/* 			triangle, */
/* 			new SimpleMaterial(Color(1.f, 0,0,1.f)), */
/* 			glm::mat4(1.f) */
/* 	) */
/* }; */

bool Lab3App::Open(){
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
