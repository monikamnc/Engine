#version 330
out vec4 color;
in vec2 uv0;
uniform sampler2D mytexture;

void main()
{
    //color = vec4(gl_FragCoord.x / 640, gl_FragCoord.y / 480, gl_FragCoord.x / gl_FragCoord.y , 1.0);
    color = texture2D(mytexture, uv0);
}