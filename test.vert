#version 410
in vec3 vertex_position;
in vec3 vertex_colour;
uniform mat4 transform;
out vec4 colour;
void main () {
	gl_Position = transform * vec4(vertex_position, 1.0f);
	colour = vec4(vertex_colour, 1.0f);
   }