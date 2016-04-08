#version 330 core

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float	Alpha;
in vec3 ourcolor;
//ÎÆÀí×ø±ê
in vec2 TexCoord;

out vec4 color;
void main()
{
	color = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),Alpha);
}