#pragma once
#include "Control/control.h"
#include "Shader/shader.h"
#include "Texture/texture.h"
#include "ObjMesh/objMesh.h"
#include "Init/initGraphics.h"

int main()
{
	if (!OpenGLInit())
	{
		std::cout << "Init failed!" << std::endl;
		return -1;
	}
	//Generate Vertex Array Object
	GLuint Vao;
	glGenVertexArrays(1, &Vao);
	glBindVertexArray(Vao);

	//shader ,texture and mesh data
	
	GLuint programID = shader::LoadShaders("VFShader/t.vs", "VFShader/t.fs");

	glUseProgram(programID);

	objMesh mesh;
	//mesh.loadAssImp("obj/table.obj");
	//mesh.loadAssImp("obj/drgon.obj");
	//mesh.loadAssImp("Taxi/taxi.obj");
	//mesh.loadAssImp("obj/surgery.obj");
	mesh.loadAssImp("SugeryTable/sugeryTable.obj");

	control c(programID);
	// Set the required callback functions
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	GLuint RenderID = glGetUniformLocation(programID, "RenderMode");
	glUniform1i(RenderID, rendermode);

	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	do {
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago
											 // printf and reset
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//鼠标，键盘的控制
		c.update();
		//光照相关
		glm::vec3 lightPos = glm::vec3(4, 4, 4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		//--------Draw--------
		mesh.render(rendermode);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &Vao);
	glfwTerminate();
	return 0;
}