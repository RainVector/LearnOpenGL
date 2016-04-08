#version 330 core

layout(location = 0) in vec3 vpositon;

void main()
{
	gl_Position = vec4(vpositon.x,vpositon.y,vpositon.z,1.0);
}