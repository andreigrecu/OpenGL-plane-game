#version 330

// TODO: get values from fragment shader
in vec3 normal;
in vec3 color;
in vec3 position;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_position;

void main()
{
	
	out_color = vec4(color , 1);
	//out_position = vec4(position, 1);
}