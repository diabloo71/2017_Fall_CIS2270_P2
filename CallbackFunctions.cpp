/**
*	Author: Sean Salinas
*	Email :	ssalinas6@cnm.edu
*   File  : CallbackFunctions.cpp
*/
#include "CallbackFunctions.h"
DIRECTION prev_direction = POS;
int counter = 0;
bool shift_pressed = false;

void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// code for keyboard button press
	if (action == GLFW_PRESS)
		printf("Keyboard button %d = '%c' pressed.\n", key, key);
    if (action == GLFW_REPEAT)
        printf("Keyboard button %d = '%c' repeat pressed.\n", key, key);
    
    // check if shift key is being held down (used in mouse_scroll_callback)
    if ((key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT) && (action == GLFW_REPEAT))
        shift_pressed = true;
    else
        shift_pressed = false;

    // move box with the up and down arrow keys
    if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
        transform.SetAngleX(++counter * 10.0f);
    else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
        transform.SetAngleX(--counter * 10.0f);
    else if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
        transform.SetAngleY(--counter * 10.0f);
    else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
        transform.SetAngleY(++counter * 10.0f);
    else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        auto_play = !auto_play;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) 
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		// code for left mouse button press
		printf("Left mouse button pressed.\n");
		speed = speed == SLOW ? FAST : SLOW;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		// code for right mouse button press
		printf("Right mouse button pressed.\n");
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		// code for middle mouse button press
		printf("Middle mouse button pressed.\n");
	}
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) 
{	
	// code for mouse scroll
    printf("Mouse scroll moved %s.\n", yoffset > 0 ? "up" : "down");
    if (yoffset > 0 && !shift_pressed)
        transform.SetAngleX(++counter*10.0f);
    else if (yoffset <= 0 && !shift_pressed)
        transform.SetAngleX(--counter*10.0f);
    else if (yoffset > 0 && shift_pressed)
        transform.SetAngleZ(++counter*10.0f);
    else if (yoffset <= 0 && shift_pressed)
        transform.SetAngleZ(--counter*10.0f);
}

void glfw_window_size_callback(GLFWwindow *window, int width, int height) 
{
	g_gl_width = width;
	g_gl_height = height;
	printf("width %i height %i\n", width, height);
}
