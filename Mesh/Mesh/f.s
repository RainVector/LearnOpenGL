#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D texture_diffuse1;
uniform int RenderMode; //������Ⱦѡ���ͼ������ͼ���������ͼ ����control.cpp�ж���
void main()
{    
	if(RenderMode == (1<<1))
	{
		color = texture(texture_diffuse1, TexCoords);
	 }
	else if (RenderMode == (1 << 0))
	{
		color = vec4(1.0,0.5,0.0,1.0);
	}
	else if(RenderMode == 0)
	{
		color = vec4(1.0,0.0,0.5,1.0);
	}
}