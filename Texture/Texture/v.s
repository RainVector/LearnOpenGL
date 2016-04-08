#version 330 core

layout(location = 0) in vec3 vpositon;
layout(location = 1) in vec3 vcolor;
layout(location = 2) in vec2 texCoord;

uniform float xOffset;
out vec3 ourcolor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(vpositon.x,vpositon.y,vpositon.z,1.0);
	ourcolor = vcolor;
	TexCoord  = vec2(texCoord.x + xOffset, texCoord.y);
}