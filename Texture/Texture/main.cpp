#include <iostream>
#include <GL/glew.h> //glewҪ��glfw֮ǰ
#include <GLFW\glfw3.h>
#include <GL\freeglut.h>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>

#include "shader.h"
#include "texture.h"
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
	shader myshader("v.s", "f.s");
	//���ö������ݣ�λ�ã���ɫ�����������
	GLfloat vertices1[] = {
		// λ��                 // ��ɫ
		//  ---- λ�� ----     ---- ��ɫ ----  ---- �������� ----
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // ����
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // ����
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// ����
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // ����
	};
	//��������
	GLuint indices[] = {
		0,1,3, //��һ��������
		1,2,3	//�ڶ���������
	};
	GLuint VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//λ������
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
	//��ɫ����
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3*sizeof(GLfloat)));
	//������������
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//���ز���������
	Texture mytexture1,mytexture2;
	mytexture1.loadTexture("container.jpg");
	mytexture2.loadTexture("awesomeface.png");
	//û��whileѭ����ʱ�򴰿����أ�whileѭ��Ҳ����Ϸѭ������GLFW�˳�֮ǰһֱ��������
	while (!glfwWindowShouldClose(window))
	{
		//�����û�д���ʲô�¼����磺����ƶ���������Ӧ�ص�����
		glfwPollEvents();

		//glClearColor��״̬���ú���������Ҫ��ջ������ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear��״̬Ӧ�ú���,����ָ����յĻ������������glClearColor�����õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);

		//����ƫ����
		GLfloat offset = 0.5f;
		glUniform1f(glGetUniformLocation(myshader.Program, "xOffset"), offset);
		//���������������ʾȨ�أ�1.0f��ֻ��ʾЦ����0.0f:ֻ��ʾ����
		GLfloat alpha = 0.0f;
		glUniform1f(glGetUniformLocation(myshader.Program, "Alpha"), alpha);
		//ʹ��shader
		myshader.Use();
		//��������Ԫ0��������������ò�����
		glActiveTexture(GL_TEXTURE0);
		mytexture1.Bind();
		glUniform1i(glGetUniformLocation(myshader.Program, "ourTexture1"), 0);
		//��������Ԫ1��������������ò�����
		glActiveTexture(GL_TEXTURE1);
		mytexture2.Bind();
		glUniform1i(glGetUniformLocation(myshader.Program, "ourTexture2"), 1);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//������������������GLFW����ÿһ��������ɫ�Ļ�������
		glfwSwapBuffers(window);
	}
	//ѭ���������ͷ�������Դ
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);


	glfwTerminate(); //�ͷ�GLFW������ڴ�
	return 0;
}