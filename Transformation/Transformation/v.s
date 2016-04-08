#version 330 core

layout(location = 0) in vec3 vpositon;
layout(location = 1) in vec3 vcolor;
layout(location = 2) in vec2 texCoord;

uniform float xOffset;
uniform mat4 transform;
out vec3 ourcolor;
out vec2 TexCoord;

void main()
{
	gl_Position = transform * vec4(vpositon.x,vpositon.y,vpositon.z,1.0f);
	ourcolor = vcolor;
	TexCoord  = vec2(texCoord.x , texCoord.y);
}