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
//Vertex �ṹ�壬��������ÿ����������
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
//Texture�ṹ�壬������֯��������
struct Texture
{
	//�洢�����id ���������ͣ�����diffuse�����specular����
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
	//���û��Ʒ�ʽ
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
