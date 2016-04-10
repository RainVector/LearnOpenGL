#ifndef MEHS_H
#define MESH_H
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include<glm/common.hpp>
#include <assimp/types.h>

#include "shader.h"
#include "control.h"
//Vertex 结构体，用来索引每个顶点属性
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
//Texture结构体，用来组织纹理数据
struct Texture
{
	//存储纹理的id 和它的类型，比如diffuse纹理或specular纹理
	GLuint id; 
	std::string type;
	aiString path;
};
class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
	//设置绘制方式
	void Draw(Shader shader, int renderMode);
	void DeleteBuffer()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};

#endif // !MEHS_H
