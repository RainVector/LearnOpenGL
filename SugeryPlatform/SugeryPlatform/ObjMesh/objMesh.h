#ifndef _OBJMESH_H
#define _OBJMESH_H
#include <string>
#include <glm/common.hpp>
#include <vector>

// Include AssImp
#include <assimp/Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "../Texture/texture.h"
//rendering mode
#define OBJMESHRENDER_VERTEX                (0)             //ֻ��Ⱦ����
#define OBJMESHRENDER_TRIANGLE              (1 << 0)       //��������
#define OBJMESHRENDER_TEXTURE               (1 << 1)       //��������

extern int rendermode;
struct Vertex {
	glm::vec3 m_pos;
	glm::vec2 m_tex;
	glm::vec3 m_normal;
	Vertex() {}
	Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal) :m_pos(pos), m_tex(tex), m_normal(normal) {}
	Vertex& operator=( Vertex m) { m_pos = m.m_pos; m_tex = m.m_tex; m_normal = m.m_normal; }
};
class objMesh {
public:
	objMesh() {};
	~objMesh() {}
	bool loadObj(const std::string& filename);
	bool loadAssImp(const std::string& path);

	void render(int renderMode);

private:
	bool InitFromScene(const aiScene* pScene, const std::string& Filename);
	void InitMesh(unsigned int Index, const aiMesh* paiMesh);
	bool InitMaterials(const aiScene* pScene, const std::string& Filename);


	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texturecoods;
	std::vector<glm::vec3> normals;


#define INVALID_MATERIAL 0xFFFFFFFF
#define INVALID_OGL_VALUE 0xffffffff
	//ÿһ��MeshEntry����һ������
	struct MeshEntry {
		MeshEntry();

		~MeshEntry();

		void Init(const std::vector<Vertex>& Vertices,
			const std::vector<unsigned int>& Indices,
			std::vector<glm::vec3> vertices);
		
		GLuint VB;	//Vertex buffer index
		GLuint IB;	//indices buffer 
		GLuint vertexbuffer;//ֻ�ж�����ά����
		unsigned int NumIndices;
		unsigned int MaterialIndex;
	};



	std::vector<MeshEntry> m_Entries;
	std::vector<texture*> m_Textures;
};
#endif // !_OBJMESH_H