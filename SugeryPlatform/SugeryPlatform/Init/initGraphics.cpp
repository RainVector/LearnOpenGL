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

	//��������
	window = glfwCreateWindow(winWidth, winHeigh, "Sugery", NULL, NULL);

	//������ڴ������ɹ����򷵻� NULL
	if (window == NULL) {
		std::cerr << "create window failed!" << std::endl;
		glfwTerminate();
		return false;
	}
	//���õ�ǰ����Ϊ�����
	glfwMakeContextCurrent(window);

	//����������Ҫ�����幦�ܰٶ�
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "glew init error!" << std::endl;
		return false;
	}
	//ȷ����escapse��������ʱ���ܱ���׽��
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//�������ͼ�꣬��������ܹ����������ƶ�
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//�����������Ļ����
	glfwPollEvents();
	glfwSetCursorPos(window, winWidth / 2, winHeigh / 2);
	//���ñ�����ɫ
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//Acepte the front fragment
	glEnable(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	return true;
}