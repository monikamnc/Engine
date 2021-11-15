#version 330
out vec4 color;

in vec2 uv0;

uniform sampler2D mytexture;

void main()
{
	color = texture2D(mytexture, uv0);
}