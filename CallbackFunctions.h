#pragma once
/**
*	Author: Sean Salinas
*	Email :	ssalinas6@cnm.edu
*   File  : CallbackFunctions.h
*/
#include <GL/glew.h>  /* include GLEW and new version of GL on Windows */
#include <GL/glfw3.h> /* GLFW helper library */
#include <stdio.h>
#include "MathFuncs.h"
#include "Transform.h"

// Extern variables
extern int g_gl_width;
extern int g_gl_height;
extern const float SLOW, FAST;
extern float speed;
extern bool auto_play;
extern Transform transform;

// Global variables
enum DIRECTION { NEG = -1, POS = 1 };


void glfw_error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void glfw_window_size_callback(GLFWwindow *window, int width, int height);