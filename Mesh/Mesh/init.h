#ifndef INIT_H
#define INIT_H
#include <iostream>
#include <GL/glew.h> //glew要在glfw之前
#include <GLFW\glfw3.h>
#include <GL\freeglut.h>
#include "control.h"
GLFWwindow* window;
bool init()
{
	//窗口管理，初始化和设置
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//OpenGL 使用核心模式
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//窗口大小不可变

											 //创建一个窗口
	window = glfwCreateWindow(width, height, "HelloWindow", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "failed to create window" << std::endl;
		glfwTerminate();
		return false;
	}
	//设置上下文
	glfwMakeContextCurrent(window);

	//可以在创建窗口之后和游戏循环之前注册各种回调函数
	glfwSetKeyCallback(window, key_callback);

	//glew用来管理OpenGL的函数指针
	glewExperimental = GL_TRUE; //设置为true是为了让GLEW在管理OpenGL的函数指针时更多地使用现代化技术，设置为false，
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to init glew!" << std::endl;
		return false;
	}
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	return true;
}

#endif // !INIT_H

