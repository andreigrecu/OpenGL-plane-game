#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 3) in vec3 v_color; 

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 color_used;


out vec3 position;
out vec3 normal;
out vec3 color;


void main()
{

	position = v_position;
	color = color_used;
	normal = v_normal;

	
	gl_Position = Projection * View * Model * vec4(position, 1.0f);
}
