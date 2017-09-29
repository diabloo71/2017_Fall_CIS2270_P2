/**
*   Author: Sean Salinas
*   Email :	ssalinas6@cnm.edu
*   File  : Bounce.cpp
*   Desc  : Project #2, Bounce with 3D Transformation.
*			Left mouse press             = change box speed (slow -> fast -> slow....)
*		    Mouse scroll up/down         = box rotate around X axis
*           Shift + mouse scroll up/down = box rotate around Z axis
*			Keys Up/Down                 = box rotate around X axis
*			Keys Left/Right              = box rotate around Y axis
*           Enter                        = turn auto play on and off(default)
*/
#include <GL/glew.h>  /* include GLEW and new version of GL on Windows */
#include <GL/glfw3.h> /* GLFW helper library */
#include "MathFuncs.h"
#include "Display.h"
#include "Shader.h"
#include "Transform.h"

int	        g_gl_width  = 600;
int         g_gl_height = 600;
const float SLOW        = 2500.0f, FAST = 1500.0f;
float       speed       = SLOW;
bool        auto_play   = false; //to allow movement performed automatically, when false user can use keyboard to move cube
Transform transform; 
GLuint matrix_Uniform;
int main() {
    const int NUM_OF_SIDES = 6; // [1,6]
    const int NUM_OF_VERT_PER_SIDE = 6;
	const int STRIDE = 6;
    const int NUM_OF_VERTICES = NUM_OF_VERT_PER_SIDE * NUM_OF_SIDES;
    GLfloat points[] = {
//         X       Y       Z      R     G     B
        -0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 1.0f, //triangle 1 of front box
         0.25f,  0.25f,  0.25f,  0.0f, 1.0f, 0.0f,
        -0.25f, -0.25f,  0.25f,  0.0f, 0.0f, 1.0f,
         0.25f,  0.25f,  0.25f,  0.0f, 1.0f, 0.0f, //triangle 2 of front box
         0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
        -0.25f, -0.25f,  0.25f,  0.0f, 0.0f, 1.0f,

        -0.25f,  0.25f, -0.25f,  1.0f, 0.0f, 1.0f, //triangle 1 of back box
         0.25f,  0.25f, -0.25f,  0.0f, 1.0f, 0.0f,
        -0.25f, -0.25f, -0.25f,  0.0f, 0.0f, 1.0f,
         0.25f,  0.25f, -0.25f,  0.0f, 1.0f, 0.0f, //triangle 2 of back box
         0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 1.0f,
        -0.25f, -0.25f, -0.25f,  0.0f, 0.0f, 1.0f,

        -0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 0.0f, //triangle 1 of left box (RED)
        -0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 0.0f,
        -0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 0.0f,
        -0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 0.0f, //triangle 2 of left box (RED)
        -0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 0.0f,
        -0.25f,  0.25f, -0.25f,  1.0f, 0.0f, 0.0f,

         0.25f,  0.25f,  0.25f,  0.0f, 1.0f, 0.0f, //triangle 1 of right box (GREEN)
         0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 0.0f,
         0.25f,  0.25f, -0.25f,  0.0f, 1.0f, 0.0f,
         0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 0.0f, //triangle 2 of right box (GREEN)
         0.25f,  0.25f,  0.25f,  0.0f, 1.0f, 0.0f,
         0.25f, -0.25f,  0.25f,  0.0f, 1.0f, 0.0f,

         0.25f,  0.25f,  0.25f,  0.0f, 0.0f, 1.0f, //triangle 1 of top box (BLUE)
         0.25f,  0.25f, -0.25f,  0.0f, 0.0f, 1.0f,
        -0.25f,  0.25f, -0.25f,  0.0f, 0.0f, 1.0f,
         0.25f,  0.25f,  0.25f,  0.0f, 0.0f, 1.0f, //triangle 2 of top box (BLUE)
        -0.25f,  0.25f, -0.25f,  0.0f, 0.0f, 1.0f,
        -0.25f,  0.25f,  0.25f,  0.0f, 0.0f, 1.0f,

         0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 1.0f, //triangle 1 of bottom box (PINK)
        -0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 1.0f,
         0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 1.0f,
         0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 1.0f, //triangle 2 of bottom box (PINK)
        -0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
        -0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 1.0f		
    };
    Display display(g_gl_width, g_gl_height, "Sean Salinas - Program 2 Bounce with 3D Transformation");
    Shader shader("test");	

    // Set up the VBO
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Set up the VAO
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Define location of positions in VBO
    GLint posAttrib = glGetAttribLocation(shader.GetProgramID(), "vertex_position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GL_FLOAT), NULL);
    glEnableVertexAttribArray(posAttrib);

    // Define location of colors in VBO
    GLint colAttrib = glGetAttribLocation(shader.GetProgramID(), "vertex_colour");
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GL_FLOAT), (char*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(colAttrib);

    const GLfloat SQUARE_WIDTH = .76f;
    float counter = 0;
    while (!display.IsClosed()) {
        // clear screen and set background to grey
        display.Clear(0.25f, 0.25f, 0.25f, 1.0f);

        if (auto_play){
            // move box along x-axis
            transform.SetPositionIt(vec3(float(sinf(counter))*SQUARE_WIDTH, 0.0f, 0.0f));
        
            // scale box (smaller and larger)
			transform.SetScaleIt(vec3(cosf(counter / 10), cosf(counter / 10), cosf(counter / 10)));

            // rotate box along x, y and z axis
            transform.SetAngleZ(counter*5);
            transform.SetAngleY(counter*15);
            transform.SetAngleX(counter*25);

            counter += 1 / speed;
        }

        shader.Use();

        // update box location using the transformation matrix
        glUniformMatrix4fv(matrix_Uniform, GL_TRUE, GL_FALSE, transform.GetModel().m);

        shader.Use();
        glViewport(0, 0, g_gl_width, g_gl_height);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, NUM_OF_VERTICES);
        display.Update();
		//counter += speed[num] / 80.0f;
    }

    return 0;
}
