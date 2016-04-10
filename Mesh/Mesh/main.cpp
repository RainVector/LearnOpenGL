#include <iostream>
#include <GL/glew.h> //glewҪ��glfw֮ǰ
#include <GLFW\glfw3.h>
#include <GL\freeglut.h>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "model.h"
#include "control.h"
//���ڵĿ�͸�
const GLuint width = 1080, height = 760;
int rendermode = OBJMESHRENDER_TEXTURE;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void Do_Movement();
// ���
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//��������Ƿ��µ�����
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
GLfloat position = 0;
//��ǰ֡����һ֡��ʱ���
GLfloat deltaTime = 0.0f;
//��һ֡���¼�
GLfloat lastFrame = 0.0f;
int main()
{
	//���ڹ�����ʼ��������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//OpenGL ʹ�ú���ģʽ
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//���ڴ�С���ɱ�

											 //����һ������
	GLFWwindow* window = glfwCreateWindow(width, height, "HelloWindow", nullptr, nullptr);
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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glew��������OpenGL�ĺ���ָ��
	glewExperimental = GL_TRUE; //����Ϊtrue��Ϊ����GLEW�ڹ���OpenGL�ĺ���ָ��ʱ�����ʹ���ִ�������������Ϊfalse��
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to init glew!" << std::endl;
		return -1;
	}
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	//shader 
	Shader myshader("v.s", "f.s");
	
	//����ģ��
	Model ourModel("nanosuit/nanosuit.obj");

	//û��whileѭ����ʱ�򴰿����أ�whileѭ��Ҳ����Ϸѭ������GLFW�˳�֮ǰһֱ��������
	while (!glfwWindowShouldClose(window))
	{
		//�����û�д���ʲô�¼����磺����ƶ���������Ӧ�ص�����
		glfwPollEvents();
		//����ͷ�ı䶯
		Do_Movement();
		//glClearColor��״̬���ú���������Ҫ��ջ������ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear��״̬Ӧ�ú���,����ָ����յĻ������������glClearColor�����õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		myshader.Use();
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// Transformation matrices
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)width / (float)height, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(myshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(myshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// Draw the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(myshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

		//ourModel.Draw(myshader);
		ourModel.Draw(myshader, rendermode);
		

		//������������������GLFW����ÿһ��������ɫ�Ļ�������
		glfwSwapBuffers(window);
	}

	ourModel.DeleteResource();


	glfwTerminate(); //�ͷ�GLFW������ڴ�
	return 0;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}


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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;

	//����rendermode,����V:��������ͼ������M:������������ͼ������T:�����������ͼ
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		rendermode = OBJMESHRENDER_VERTEX;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		rendermode = OBJMESHRENDER_TRIANGLE;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		rendermode = OBJMESHRENDER_TEXTURE;
}