#ifndef CONTROL_H
#define CONTROL_H
#include <iostream>
#include <GL/glew.h> //glew要在glfw之前
#include <GLFW\glfw3.h>
#include <GL\freeglut.h>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "common.h"
#include "shader.h"
#include "camera.h"
#ifdef HI



const GLuint width = 1024, height = 760;
class control
{
public:
	control() 
	{
		deltaTime = 0.0f;
		lastFrame = 0.0f;
		lastX = 400, lastY = 300;
		firstMouse = true;
		Camera cameratmp(glm::vec3(0.0f, 0.0f, 3.0f));
		camera = cameratmp;
	}
	 void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	 void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	 void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	 void Do_Movement();
	 void reshape(Shader shader);
private:
	 GLfloat currentFrame;
	 GLfloat deltaTime;
	 GLfloat lastFrame;
	
	 Camera camera;
	 bool keys[1024];
	 GLfloat lastX , lastY;
	 bool firstMouse ;
};

void control::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
void control::mouse_callback(GLFWwindow* window, double xpos, double ypos)
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
void control::Do_Movement()
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
*第一个参数是GLFWwindow指针；
*第二个整形参数用来表示事件的按键；
*第三个整形参数描述用户是否有第二个键按下或释放；
*第四个整形参数表示事件类型，如按下或释放；
*最后一个参数是表示是否有Ctrl、Shift、Alt、Super等按钮的操作。
*GLFW会在恰当的时候调用它，并为各个参数传入适当的值。
*/
void control::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;

	//设置rendermode,按键V:画出顶点图，按键M:画出三角网格图，按键T:画出有纹理的图
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		rendermode = OBJMESHRENDER_VERTEX;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		rendermode = OBJMESHRENDER_TRIANGLE;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		rendermode = OBJMESHRENDER_TEXTURE;
}
inline void control::reshape(Shader shader)
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	// Transformation matrices
	glm::mat4 projection = glm::perspective(camera.Zoom, (float)width / (float)height, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

	// Draw the loaded model
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
}
#endif // HI
#endif // !CONTROL_H
