#include <iostream>
#include <GL/glew.h> //glew要在glfw之前
#include <GLFW\glfw3.h>
#include <GL\freeglut.h>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
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
	shader myshader("v.s", "f.s");
	//设置顶点数据，位置，颜色，法向等属性
	GLfloat vertices1[] = {
		// 位置                 // 颜色
		//  ---- 位置 ----     ---- 颜色 ----  ---- 纹理坐标 ----
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // 右上
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// 左下
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // 左上
	};
	//顶点索引
	GLuint indices[] = {
		0,1,3, //第一个三角形
		1,2,3	//第二个三角形
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

	//位置属性
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
	//颜色属性
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3*sizeof(GLfloat)));
	//纹理坐标属性
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//加载并创建纹理
	Texture mytexture1,mytexture2;
	mytexture1.loadTexture("container.jpg");
	mytexture2.loadTexture("awesomeface.png");

	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//vec = trans * vec;
	std::cout << "After translation vec = " << vec.x << vec.y << vec.z << std::endl;

	//没有while循环的时候窗口闪关，while循环也称游戏循环，在GLFW退出之前一直保持运行
	while (!glfwWindowShouldClose(window))
	{
		//检查有没有触发什么事件，如：鼠标移动，调用相应回调函数
		glfwPollEvents();

		//glClearColor是状态设置函数，设置要清空缓冲的颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear是状态应用函数,整个指定清空的缓冲区都被填充glClearColor所设置的颜色
		glClear(GL_COLOR_BUFFER_BIT);

		//旋转物体的矩阵
		glm::mat4 trans;
		//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
		trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.5f));

		trans = glm::rotate(trans, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		GLint loc = glGetUniformLocation(myshader.Program, "transform");
		glUniformMatrix4fv(loc,1,GL_FALSE,glm::value_ptr( trans));
		//设置偏移量
		GLfloat offset = 0.5f;
		glUniform1f(glGetUniformLocation(myshader.Program, "xOffset"), offset);
		//设置两个纹理的显示权重，1.0f：只显示笑脸，0.0f:只显示方形
		GLfloat alpha = 0.5f;
		glUniform1f(glGetUniformLocation(myshader.Program, "Alpha"), alpha);
		//使用shader
		myshader.Use();
		//激活纹理单元0，绑定纹理对象，设置采样器
		glActiveTexture(GL_TEXTURE0);
		mytexture1.Bind();
		glUniform1i(glGetUniformLocation(myshader.Program, "ourTexture1"), 0);
		//激活纹理单元1，绑定纹理对象，设置采样器
		glActiveTexture(GL_TEXTURE1);
		mytexture2.Bind();
		glUniform1i(glGetUniformLocation(myshader.Program, "ourTexture2"), 1);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//交换缓冲区（储存着GLFW窗口每一个像素颜色的缓冲区）
		glfwSwapBuffers(window);
	}
	//循环结束后，释放所有资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);


	glfwTerminate(); //释放GLFW分配的内存
	return 0;
}