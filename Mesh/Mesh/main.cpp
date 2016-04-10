#include <iostream>
#include <GL/glew.h> //glew要在glfw之前
#include <GLFW\glfw3.h>
#include <GL\freeglut.h>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "model.h"
#include "control.h"
//窗口的宽和高
const GLuint width = 1080, height = 760;
int rendermode = OBJMESHRENDER_TEXTURE;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void Do_Movement();
// 相机
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//储存键盘是否按下的数组
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
GLfloat position = 0;
//当前帧与上一帧的时间差
GLfloat deltaTime = 0.0f;
//上一帧的事件
GLfloat lastFrame = 0.0f;
int main()
{
	//窗口管理，初始化和设置
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//OpenGL 使用核心模式
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//窗口大小不可变

											 //创建一个窗口
	GLFWwindow* window = glfwCreateWindow(width, height, "HelloWindow", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//设置上下文
	glfwMakeContextCurrent(window);
	
	//可以在创建窗口之后和游戏循环之前注册各种回调函数
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glew用来管理OpenGL的函数指针
	glewExperimental = GL_TRUE; //设置为true是为了让GLEW在管理OpenGL的函数指针时更多地使用现代化技术，设置为false，
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to init glew!" << std::endl;
		return -1;
	}
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	//shader 
	Shader myshader("v.s", "f.s");
	
	//加载模型
	Model ourModel("nanosuit/nanosuit.obj");

	//没有while循环的时候窗口闪关，while循环也称游戏循环，在GLFW退出之前一直保持运行
	while (!glfwWindowShouldClose(window))
	{
		//检查有没有触发什么事件，如：鼠标移动，调用相应回调函数
		glfwPollEvents();
		//处理镜头的变动
		Do_Movement();
		//glClearColor是状态设置函数，设置要清空缓冲的颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear是状态应用函数,整个指定清空的缓冲区都被填充glClearColor所设置的颜色
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
		

		//交换缓冲区（储存着GLFW窗口每一个像素颜色的缓冲区）
		glfwSwapBuffers(window);
	}

	ourModel.DeleteResource();


	glfwTerminate(); //释放GLFW分配的内存
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
*第一个参数是GLFWwindow指针；
*第二个整形参数用来表示事件的按键；
*第三个整形参数描述用户是否有第二个键按下或释放；
*第四个整形参数表示事件类型，如按下或释放；
*最后一个参数是表示是否有Ctrl、Shift、Alt、Super等按钮的操作。
*GLFW会在恰当的时候调用它，并为各个参数传入适当的值。
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
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