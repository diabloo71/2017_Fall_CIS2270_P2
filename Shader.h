#pragma once
/**
*	Author: Ivonne Nelson
*	Email :	ssalinas6@cnm.edu
*   File  : Shader.h
*/
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>  /* include GLEW and new version of GL on Windows */
#include <GL/glfw3.h> /* GLFW helper library */

class Shader
{
public:
	Shader(const std::string& filename);
	void Use();	//Means use this one
	GLuint GetProgramID() { return programID; }
	virtual ~Shader();
private:
	GLuint programID;
	static const GLuint NUM_SHADERS = 2;
	GLuint shaders[NUM_SHADERS];
	static std::string LoadShader(const std::string& fileName);
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	static GLuint CreateShader(const std::string& text, GLenum  shaderType);//full text of shader
};
