#include <iostream>
#include <GL/glew.h> //glew要在glfw之前
#include <GLFW\glfw3.h>
#include <GL\freeglut.h>

#include "shader.h"
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
	// 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
	// 关闭应用程序
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}



int main()
{
	//窗口管理，初始化和设置
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//OpenGL 使用核心模式
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//窗口大小不可变

											 //创建一个窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWindow", nullptr, nullptr);
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

	//glew用来管理OpenGL的函数指针
	glewExperimental = GL_TRUE; //设置为true是为了让GLEW在管理OpenGL的函数指针时更多地使用现代化技术，设置为false，
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to init glew!" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);


	//shader 
	GLuint programID = shader::LoadShaders("v.s", "f.s");
	//设置顶点数据，位置，颜色，法向等属性
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left  
		0.5f, -0.5f, 0.0f, // Right 
		0.0f,  0.5f, 0.0f  // Top 
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//先绑定顶点数组对象（VAO），然后绑定顶点缓存对象(VBO)和属性指针(attribute pointer)
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//在使用glVertexAttribPointer之后，VBO就是当前上下文绑定对象，所以现在我们可以进行解绑操作
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//解绑VAO，用完VAO之后解绑是一个好的习惯
	glBindVertexArray(0);

	//没有while循环的时候窗口闪关，while循环也称游戏循环，在GLFW退出之前一直保持运行
	while (!glfwWindowShouldClose(window))
	{
		//检查有没有触发什么事件，如：鼠标移动，调用相应回调函数
		glfwPollEvents();

		//glClearColor是状态设置函数，设置要清空缓冲的颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear是状态应用函数,整个指定清空的缓冲区都被填充glClearColor所设置的颜色
		glClear(GL_COLOR_BUFFER_BIT);

		//画三角形
		glUseProgram(programID);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//交换缓冲区（储存着GLFW窗口每一个像素颜色的缓冲区）
		glfwSwapBuffers(window);
	}
	//循环结束后，释放所有资源
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);


	glfwTerminate(); //释放GLFW分配的内存
	return 0;
}