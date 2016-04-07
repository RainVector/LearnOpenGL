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

//设置窗口的大小和窗口名
const GLuint winWidth = 1024, winHeigh = 768;
//extern const char* winTitle = "Surgery";


//glfw窗口管理程序，glew：glut扩展库的初始化
/*
* 初始化与窗口相关的东西
* 返回值： 如果初始化失败：false, 成功：true
*/
bool OpenGLInit();
#endif // !INIT_GRAPHICS_H

