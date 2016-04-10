#ifndef _SHADER_H
#define _SHADER_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
class Shader
{
public:
	//����ID
	GLuint Program;
	//���캯����ȡ������Shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//ʹ��Program
	void Use();

};

#endif // !_SHADER_H