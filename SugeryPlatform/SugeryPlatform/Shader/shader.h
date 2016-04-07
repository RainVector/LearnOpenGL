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
	shader() {};

	static GLuint LoadShaders(const std::string& vshader, const std::string& fshader);
private:

};

#endif // !_SHADER_H

