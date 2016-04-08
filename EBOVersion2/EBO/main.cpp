#include <iostream>
#include <GL/glew.h> //glewҪ��glfw֮ǰ
#include <GLFW\glfw3.h>
#include <GL\freeglut.h>

#include "shader.h"
/*
*��һ��������GLFWwindowָ�룻
*�ڶ������β���������ʾ�¼��İ�����
*���������β��������û��Ƿ��еڶ��������»��ͷţ�
*���ĸ����β�����ʾ�¼����ͣ��簴�»��ͷţ�
*���һ�������Ǳ�ʾ�Ƿ���Ctrl��Shift��Alt��Super�Ȱ�ť�Ĳ�����
*GLFW����ǡ����ʱ�����������Ϊ�������������ʵ���ֵ��
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ���û�����ESC��,��������window���ڵ�WindowShouldClose����Ϊtrue
	// �ر�Ӧ�ó���
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}



int main()
{
	//���ڹ�����ʼ��������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//OpenGL ʹ�ú���ģʽ
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//���ڴ�С���ɱ�

											 //����һ������
	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWindow", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//����������
	glfwMakeContextCurrent(window);

	//�����ڴ�������֮�����Ϸѭ��֮ǰע����ֻص�����
	glfwSetKeyCallback(window, key_callback);

	//glew��������OpenGL�ĺ���ָ��
	glewExperimental = GL_TRUE; //����Ϊtrue��Ϊ����GLEW�ڹ���OpenGL�ĺ���ָ��ʱ�����ʹ���ִ�������������Ϊfalse��
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to init glew!" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);


	//shader 
	GLuint programID1 = shader::LoadShaders("v.s", "f.s");
	GLuint programID2 = shader::LoadShaders("v.s", "f1.s");
	//���ö������ݣ�λ�ã���ɫ�����������
	GLfloat vertices1[] = {
		-0.9f, -0.5f, 0.0f,  // Left 
		-0.0f, -0.5f, 0.0f,  // Right
		-0.45f, 0.5f, 0.0f,  // Top 
	};
	GLfloat vertices2[] = {
		0.0f, -0.5f, 0.0f,  // Left
		0.9f, -0.5f, 0.0f,  // Right
		0.45f, 0.5f, 0.0f   // Top 
	};

	GLuint VBO[2], VAO[2];

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	//��һ��������
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//�ڶ���������
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//û��whileѭ����ʱ�򴰿����أ�whileѭ��Ҳ����Ϸѭ������GLFW�˳�֮ǰһֱ��������
	while (!glfwWindowShouldClose(window))
	{
		//�����û�д���ʲô�¼����磺����ƶ���������Ӧ�ص�����
		glfwPollEvents();

		//glClearColor��״̬���ú���������Ҫ��ջ������ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear��״̬Ӧ�ú���,����ָ����յĻ������������glClearColor�����õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);

		//��������
		glUseProgram(programID1);
		//����һ��������
		glBindVertexArray(VAO[0]);	
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glUseProgram(programID2);
		//���ڶ���������
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		//������������������GLFW����ÿһ��������ɫ�Ļ�������
		glfwSwapBuffers(window);
	}
	//ѭ���������ͷ�������Դ
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);


	glfwTerminate(); //�ͷ�GLFW������ڴ�
	return 0;
}