#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
#include "common.h"
class Model
{
public:
	Model(GLchar * path)
	{
		this->loadModel(path);
	}
	void Draw(Shader shader);
	void Draw(Shader shader, int rendermode);
	void DeleteResource()
	{
		for (auto &t : meshes)
			t.DeleteBuffer();
	}
private:
	//模型数据
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;
	//私有成员函数
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	GLuint TextureFromFile(const char* path,std::string filepath);
};
#endif // !MODEL_H
