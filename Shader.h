#pragma once
#include <GL\glew.h>
#include <vector>
#include <string>
#include <fstream>
class Shader
{
public:
	~Shader();
	// load in our vertex shader file and fragment shader file
	Shader(const char* vertexFilePath, const char* fragmentFilePath);
	GLuint program;
	void use();
};

