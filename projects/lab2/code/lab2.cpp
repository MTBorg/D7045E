//------------------------------------------------------------------------------
// lab2.cpp
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "lab2.h"
#include "node.h"
#include "types.h"
#include "util.h"
#include "validation.h"
#include "convex_hull.h"
#include "triangulation.h"
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <map>
#include <algorithm>

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

#define TREE_OUTLINE_COLOR 1.f,0,0,1.f
#define TREE_FILL_COLOR 1.f,1.f,1.f,1.f
#define VERTEX_COLOR 0,0,1.f,1.f
#define BACKGROUND_COLOR 1.f,1.f,1.f,1.f
#define ROTATION_SPEED 0.01f

struct IndexTriangle{
	unsigned long int i1, i2, i3;
};

int redIndex = 0;
int greenIndex = 1;
int blueIndex = 2;

std::vector<glvec> vertices;
std::vector<glvec> hull;
int cIndex = -1;
std::vector<glvec> tree;
std::vector<IndexTriangle> indexTree;
std::vector<unsigned int> hullIndices;
std::vector<unsigned int> vertexIndices;
std::vector<IndexTriangle> treeIndices;
std::vector<GLfloat> vertexBuffer;

std::vector<glvec> readFile(std::string file){
	std::vector<glvec> result;
	std::ifstream inf(file);

	if(!inf){
		std::cerr << "Could not read points file";
		exit(1);
	}
	
	// Read first line 
	// First line should specify points
	std::string firstLine;
	getline(inf, firstLine);
	size_t lines = std::stoi(firstLine);
	result.reserve(lines);

	for(size_t i = 0; i < lines; i++){
		std::string firstNum;
		inf >> firstNum;
		std::string secondNum;
		inf >> secondNum;
		result.emplace_back(std::stof(firstNum), std::stof(secondNum));
	}

	return result;
}

glm::vec4 interpolateColor(const glvec& point){
	float32
		redDist =  glm::distance(point, vertices[redIndex]),
		greenDist =  glm::distance(point, vertices[greenIndex]),
		blueDist =  glm::distance(point, vertices[blueIndex]);

	float32 alpha = 1;
	// If outside the triangled spanned by the three color points
	if(!pointInsideTriangle(
			point, vertices[redIndex], vertices[greenIndex], vertices[blueIndex])
			&& point != vertices[redIndex]
			&& point != vertices[greenIndex]
			&& point != vertices[blueIndex]
		){
		float minDist = 10; //Distance can never be greater than sqrt(8)
		for(const auto& hullPoint: hull){
			float dist = glm::distance(point, hullPoint);
			if(dist < minDist) minDist = dist;
		}
		// This would make wore sense if it would be minDist / sqrt(8) but that makes
		// it really difficult to see the vertices
		alpha = minDist;
	}

	// Divide the distance with sqrt(9) because that's the maximum distance
	return glm::vec4(redDist/sqrt(8), greenDist/sqrt(8), blueDist/sqrt(8), alpha);
}

glm::vec4 colorVertex(const glvec& vertex){
	auto color = glm::vec4(VERTEX_COLOR);
	if(vertex == vertices[redIndex]){
		color = glm::vec4(1.f,0,0,1.f);
	}else if(vertex == vertices[greenIndex]){
		color = glm::vec4(0,1.f,0,1.f);
	}else if(vertex == vertices[blueIndex]){
		color = glm::vec4(0,0,1.f,1.f);
	}else{
		color = interpolateColor(vertex);
	}
	return color;
}

/*
 * Creates a buffer containing triplets of indices corresponding to the corners of 
 * a triangle given lists of triangles and unique vertices.
 */
std::vector<IndexTriangle> createTriangleIndexBuffer(
	const std::vector<glvec>& triangleVertices,
	const std::vector<glvec>& vertices){

	auto res = std::vector<IndexTriangle>();
	for(auto it = triangleVertices.begin(); it <= triangleVertices.end() - 3; ++it){
		res.emplace_back(
			IndexTriangle{
				(unsigned long int)(std::find(vertices.begin(), vertices.end(), *it) - vertices.begin()),
				(unsigned long int)(std::find(vertices.begin(), vertices.end(), *(it+1)) - vertices.begin()),
				(unsigned long int)(std::find(vertices.begin(), vertices.end(), *(it+2)) - vertices.begin())
			}
		);
	}
	return res;
}

std::vector<GLfloat> createVertexBuffer(std::vector<glvec> vertices){
	auto noDuplicates = removeDuplicates(vertices);
	auto res = std::vector<GLfloat>();
	//Each vertex consists of two coordinates and four color values, totalling six values.
	res.reserve(noDuplicates.size() * 6); 
	for(const auto& vertex: noDuplicates){
		auto color = colorVertex(vertex);
		res.push_back(vertex.x);
		res.push_back(vertex.y);
		res.push_back(color.r);
		res.push_back(color.g);
		res.push_back(color.b);
		/* res.push_back(color.a); */
		res.push_back(1.f);
	}
	return res;
}

std::vector<unsigned int> createHullIndexBuffer(
		const std::vector<glvec>& hull,
		const std::vector<GLfloat>& vertexBuffer,
		unsigned long bufferStride){
	auto res = std::vector<unsigned int>();
	for(const auto& vertex: hull){
		res.push_back(
			getVertexIndexFromVertexBuffer(vertex, vertexBuffer, bufferStride)
		);
	}
	return res;
}

std::vector<unsigned int> createVertexIndexBuffer(
		const std::vector<glvec>& vertices,
		const std::vector<GLfloat>& vertexBuffer,
		const unsigned int bufferStride){
	auto res = std::vector<unsigned int>();
	for(const auto& vertex: vertices){
		res.push_back(
			getVertexIndexFromVertexBuffer(vertex, vertexBuffer, bufferStride)
		);
	}
	return res;
}

std::vector<IndexTriangle> createTreeIndexBuffer(
		const std::vector<glvec>& treeVertices,
		const std::vector<GLfloat>& vertexBuffer,
		const unsigned int bufferStride
	){
	auto res = std::vector<IndexTriangle>();
	for(auto it = treeVertices.begin(); it <= treeVertices.end() - 3; it+=3){
		IndexTriangle t;
		t.i1 = getVertexIndexFromVertexBuffer(*it, vertexBuffer, bufferStride);
		t.i2 = getVertexIndexFromVertexBuffer(*(it+1), vertexBuffer, bufferStride);
		t.i3 = getVertexIndexFromVertexBuffer(*(it+2), vertexBuffer, bufferStride);
		res.push_back(t);
	}
	return res;
}

void generateRandomTriangulationSet(const unsigned int size){
	do{
		vertices = generateRandomPoints(size);
		hull = convexHull(vertices);
	}while(
			!validation::originIsInConvexHull(hull) ||
			validation::duplicatePoints(vertices)
	);
	/* vertices = readFile("pointsets/square.txt"); */
	/* 	hull = convexHull(vertices); */
	
	// Create new hull with the first element appended as the last
	auto hullTemp = hull;
	hullTemp.push_back(hullTemp[0]);

	// Initial fan triangulation
	cIndex = pickPointNotOnConvexHull(vertices, hullTemp);
	Node* root = buildTree(vertices[cIndex], hullTemp, nullptr);

	// Insert the rest of the points that's not on the hull and is not
	// the point for the initial fan triangulation
	for(const auto& point: vertices){
		auto res = std::find(hull.begin(), hull.end(), point);
		if(res == hull.end() && point != vertices[cIndex]){
			root->insertPoint(point);
		}
	}
	tree = root->toPointVec();
}

Lab2App::Lab2App(){} 
Lab2App::~Lab2App(){} 

void Lab2App::updateVertexBuffer(){
		// do stuff
		// setup vbo
		glGenBuffers(1, &this->triangle);
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glUseProgram(this->program);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) + sizeof(glm::vec4), NULL);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glm::vec2) + sizeof(glm::vec4),
			(GLvoid*)sizeof(glm::vec2)
		);
		glEnableVertexAttribArray(1);
		vertexBuffer = createVertexBuffer(vertices);
		glBufferData(
				GL_ARRAY_BUFFER,
				vertexBuffer.size() * sizeof(GLfloat),
				&vertexBuffer[0],
				GL_DYNAMIC_DRAW
		);

		// Compute the index buffers
		const unsigned int bufferStride = 6;
		hullIndices = createHullIndexBuffer(hull, vertexBuffer, bufferStride);
		vertexIndices = createVertexIndexBuffer(vertices, vertexBuffer, bufferStride);
		treeIndices = createTreeIndexBuffer(tree, vertexBuffer, bufferStride);
}

void Lab2App::handleKeyPress(int32 keyCode, int32 action){
	static bool insertMode = false;
	static unsigned int randomSum = 0;
	static unsigned int inputCount = 0;
	if(action == GLFW_RELEASE){
		if(keyCode == GLFW_KEY_R){
			printf("Enter the number of point to generate:\n");
			insertMode = true;
		}else if(keyCode == GLFW_KEY_ENTER && insertMode){
			insertMode = false;
			if(randomSum <= 3){
				printf("Please enter a number bigger than 3\n");
			}else{
				generateRandomTriangulationSet(randomSum);
				updateVertexBuffer();
			}
			randomSum = inputCount = 0;
		}else if(keyCode >= GLFW_KEY_0 && keyCode <= GLFW_KEY_9 && insertMode){
			randomSum *= 10;
			randomSum += (keyCode - GLFW_KEY_0);
			inputCount++;
		}else if(keyCode == 256){ //Esc
			this->window->Close();
		}else if(insertMode){
			printf("Please enter numbers\n");
		}
	}
}

bool Lab2App::Open(){
	printf("generating points...\n");

	generateRandomTriangulationSet(5);

	App::Open();
	this->window = new Display::Window;
	this->window->SetSize(500,500);
	window->SetKeyPressFunction([this](int32 keyCode, int32, int32 action, int32)
	{
		handleKeyPress(keyCode, action);
	});

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(BACKGROUND_COLOR);

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

		updateVertexBuffer();


		// Enable alpha channel
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		return true;
	}
	return false;
}

void Lab2App::Run(){
	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();

		//Draw hull
		GLuint ibo;
		// setup index buffer
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				hullIndices.size() * sizeof(unsigned int),
				&hullIndices[0],
				GL_DYNAMIC_DRAW
				);
		glDrawElements(GL_LINE_LOOP, hullIndices.size(), GL_UNSIGNED_INT, nullptr);

		//Draw vertices
		// setup index buffer
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glPointSize(10);
		glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				vertexIndices.size() * sizeof(unsigned int),
				&vertexIndices[0],
				GL_DYNAMIC_DRAW
				);
		glDrawElements(GL_POINTS, vertexIndices.size(), GL_UNSIGNED_INT, nullptr);

		static float angle = 0;
		angle += ROTATION_SPEED;

		GLint angleUniform = glGetUniformLocation(this->program, "angle");
		if(angleUniform != 1){
			glUniform1f(angleUniform, angle);
		}else{
			printf("Failed, to locate uniform angle\n");
		}

		//Draw tree
		for(const auto& triangle: treeIndices){
			unsigned int buf[] = {triangle.i1, triangle.i2, triangle.i3};
			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(
					GL_ELEMENT_ARRAY_BUFFER,
					3 * sizeof(unsigned int),
					&buf[0],
					GL_DYNAMIC_DRAW
					);
			glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, nullptr);
		}
		this->window->SwapBuffers();
	}
}
