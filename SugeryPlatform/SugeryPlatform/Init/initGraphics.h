#ifndef INIT_GRAPHICS_H
#define INIT_GRAPHICS_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;
extern GLFWwindow *window;

//���ô��ڵĴ�С�ʹ�����
const GLuint winWidth = 1024, winHeigh = 768;
//extern const char* winTitle = "Surgery";


//glfw���ڹ������glew��glut��չ��ĳ�ʼ��
/*
* ��ʼ���봰����صĶ���
* ����ֵ�� �����ʼ��ʧ�ܣ�false, �ɹ���true
*/
bool OpenGLInit();
#endif // !INIT_GRAPHICS_H

