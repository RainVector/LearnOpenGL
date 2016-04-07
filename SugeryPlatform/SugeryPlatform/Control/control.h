#ifndef CONTROL_H
#define CONTROL_H
// Include GLFW
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Init/initGraphics.h"
#include "../ObjMesh/objMesh.h"
using namespace glm;

class control {
public:
	control();
	control(GLuint pID);
	//处理鼠标键盘输入，更新视窗
	void update();
private:

	void computeMatricesFromInputs();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	GLuint programID;
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;


};
#endif // !CONTROL_H
