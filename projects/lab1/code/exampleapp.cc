//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include <glm/glm.hpp>
#include <glm/vec2.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>
#include <iostream>
#include <math.h>

const GLchar* vs =
"#version 310 es\n"
"precision mediump float;\n"
"layout(location=0) in vec2 pos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(pos, -1, 1);\n"
"}\n";

const GLchar* ps =
"#version 310 es\n"
"precision mediump float;\n"
"layout(location=0) in vec4 color;\n"
"out vec4 Color;\n"
"void main()\n"
"{\n"
"	Color = vec4(1, 0,0,0);\n"
"}\n";

using namespace Display;

auto vertices = std::vector<glm::vec2>();
struct Triangle{
	glm::vec2 q0, a, q1;
	Triangle(glm::vec2 q0, glm::vec2 a ,glm::vec2 q1)
		:q0(q0),a(a),q1(q1){}
};

int depth = 0;

namespace Example
{

//------------------------------------------------------------------------------
/**
*/
ExampleApp::ExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
ExampleApp::~ExampleApp()
{
	// empty
}

glm::vec2 calcNextBase(glm::vec2 a, glm::vec2 b){
	return (a * 2.f + b) / 3.f;
}

Triangle koch_triangle(glm::vec2 p0, glm::vec2 p1, glm::vec2 b){
	auto q0 = (p0*2.0f+p1)/3.f;
	auto q1 = (p0+p1*2.0f)/3.f;
	auto m = (p0 + p1) / 2.f;
	
	// Calculate the length (height) of the adjacent side of the right triangle formed by q0,
	// m and a.
	// The length of the hypotenuse is known to be a third of the length of the vector
	// p1 - p2.
	auto a_height = sqrtf(powf(glm::length(p1 - p0)/3.f,2.f) - powf(glm::length(p1 - p0)/6.f, 2.f));
	
	// Normalize m - b  and multiply it with the height of a, and then add it to m 
	// in order to get vector a.
	auto a = (glm::normalize(m - b) * (float)a_height) + m;
	
	return Triangle(q0, a, q1);
}

std::vector<glm::vec2> koch_side(glm::vec2 a,glm::vec2 b, glm::vec2 c, int depth){
	if(depth == 0){
		return {a,b};
	}

	// Calculate the new triangle
	auto t = koch_triangle(a,b,c);

	// Recurse over the sides
	auto t_1 = koch_side(a, t.q0, calcNextBase(a,c), depth - 1);
	auto t_2 = koch_side(t.q0, t.a, t.q1, depth - 1);
	auto t_3 = koch_side(t.a, t.q1, t.q0, depth - 1);
	auto t_4 = koch_side(t.q1, b, calcNextBase(b,c), depth-1);

	auto res = std::vector<glm::vec2>();
	res.insert(res.end(), t_1.begin(), t_1.end());
	res.insert(res.end(), t_2.begin(), t_2.end());
	res.insert(res.end(), t_3.begin(), t_3.end());
	res.insert(res.end(), t_4.begin(), t_4.end());

	return res;
}

std::vector<glm::vec2> createSnowFlake(const int depth){
	//Initial coordinates
	auto a =	glm::vec2(-0.866f/1.5f, -0.5f/1.5f);
	auto b =	glm::vec2(0.0f/1.5f, 1.0f/1.5f);
	auto c =	glm::vec2(0.866f/1.5f, -0.5f/1.5f);

	// Calculate the sides
	auto temp_1 = koch_side(a,b,c,depth);
	auto temp_2 = koch_side(b,c,a,depth);	
	auto temp_3 = koch_side(c,a,b,depth);

	auto res = std::vector<glm::vec2>();
	res.insert(res.end(), temp_1.begin(), temp_1.end()); 
	res.insert(res.end(), temp_2.begin(), temp_2.end()); 
	res.insert(res.end(), temp_3.begin(), temp_3.end()); 
	return res;
}



//------------------------------------------------------------------------------
/**
*/
bool
ExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	this->window->SetSize(500,500);
	window->SetKeyPressFunction([this](int32 keyCode, int32, int32, int32)
	{
		static int lastKey = -1;
		if(keyCode == 256){ //Esc
			this->window->Close();
		}else if(keyCode >= 48 && keyCode <= 55){ //key 0 to 7
			int key = keyCode - 48;
			if(key != lastKey){
				lastKey = key;
				vertices = createSnowFlake(key);
			}
		}
	});

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.4f, 0.4f, 0.f, 7.0f);

		// setup vertex shader
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLint length = (GLint)std::strlen(vs);
		glShaderSource(this->vertexShader, 1, &vs, &length);
		glCompileShader(this->vertexShader);

		// get error log
		GLint shaderLogSize;
		glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// setup pixel shader
		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
		length = (GLint)std::strlen(ps);
		glShaderSource(this->pixelShader, 1, &ps, &length);
		glCompileShader(this->pixelShader);

		// get error log
		shaderLogSize;
		glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// create a program object
		this->program = glCreateProgram();
		glAttachShader(this->program, this->vertexShader);
		glAttachShader(this->program, this->pixelShader);
		glLinkProgram(this->program);
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
			printf("[PROGRAM LINK ERROR]: %s", buf);
			delete[] buf;
		}

		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
ExampleApp::Run()
{
	// Create koch snowflake
	vertices = createSnowFlake(5);

	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();

		// do stuff
		// setup vbo
		glGenBuffers(1, &this->triangle);
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glUseProgram(this->program);
		glEnableVertexAttribArray(0);
		/* glEnableVertexAttribArray(1); */
		/* glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, NULL); */
		/* glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, (GLvoid*)(sizeof(float32) * 3)); */
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), NULL);
		/* glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, (GLvoid*)(sizeof(float32) * vertices.size())); */
		glDrawArrays(GL_LINE_LOOP, 0, vertices.size());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		this->window->SwapBuffers();
	}
}

} // namespace Example
