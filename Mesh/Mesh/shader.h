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
	//程序ID
	GLuint Program;
	//构造函数读取并创建Shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//使用Program
	void Use();

};

#endif // !_SHADER_H