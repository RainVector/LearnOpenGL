#pragma once
#include "initGraphics.h"
GLFWwindow * window;
bool OpenGLInit() {
	//-----------------------------------Init--------------------------------
	if (!glfwInit()) {
		std::cerr << "glfwInit failed!" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	window = glfwCreateWindow(winWidth, winHeigh, "Sugery", NULL, NULL);

	//如果窗口创建不成功，则返回 NULL
	if (window == NULL) {
		std::cerr << "create window failed!" << std::endl;
		glfwTerminate();
		return false;
	}
	//设置当前窗口为激活窗口
	glfwMakeContextCurrent(window);

	//下面这句很重要，具体功能百度
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "glew init error!" << std::endl;
		return false;
	}
	//确保当escapse键被按下时，能被捕捉到
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//隐藏鼠标图标，并且鼠标能够不受限制移动
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//设置鼠标在屏幕中心
	glfwPollEvents();
	glfwSetCursorPos(window, winWidth / 2, winHeigh / 2);
	//设置背景颜色
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//设置深度测试
	glEnable(GL_DEPTH_TEST);
	//Acepte the front fragment
	glEnable(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	return true;
}