#version 330 core

layout(location = 0) in vec3 vpositon;
layout(location = 1) in vec3 vcolor;

uniform float xOffset;

out vec3 ourcolor;
void main()
{
	gl_Position = vec4(vpositon.x + xOffset,vpositon.y,vpositon.z,1.0);
	ourcolor = vpositon;
}