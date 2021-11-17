#version 330
layout(location=0) in vec3 my_vertex_position;
layout(location=1) in vec2 my_vertex_uv0;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec2 uv0;

void main()
{
	gl_Position = proj*view*model*vec4(my_vertex_position, 1.0);
	//gl_Position = vec4(my_vertex_position, 1.0);
	uv0 = my_vertex_uv0;
}