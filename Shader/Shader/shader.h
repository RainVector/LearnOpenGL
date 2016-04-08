#ifndef _SHADER_H
#define _SHADER_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
class shader
{
public:
	//����ID
	GLuint Program;
	//���캯����ȡ������Shader
	shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//ʹ��Program
	void Use();

};

#endif // !_SHADER_H