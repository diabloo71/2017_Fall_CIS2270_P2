#pragma once
/**
*	Author: Ivonne Nelson
*	Email :	ssalinas6@cnm.edu
*   File  : Display.h
*/
#include <GL/glew.h>  /* include GLEW and new version of GL on Windows */
#include <GL/glfw3.h> /* GLFW helper library */
#include <iostream>
#include "MathFuncs.h"
#include "CallbackFunctions.h"

class Display
{
public:
	Display(int width, int height, const std::string& title);
	void Update();
	void Clear(float r, float g, float b, float a);
	bool IsClosed() { return isClosed; }
	virtual ~Display();

private:
	GLFWwindow*  window;
	bool isClosed = false;
};
