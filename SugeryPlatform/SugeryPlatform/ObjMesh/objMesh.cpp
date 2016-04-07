#pragma once
#pragma warning(disable:4996)

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GL/freeglut.h>


#include "objMesh.h"
int rendermode = OBJMESHRENDER_TEXTURE;//默认显示加载了纹理的图形
//int rendermode = -1;//默认显示加载了纹理的图形
void objMesh::MeshEntry::Init(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices, std::vector<glm::vec3> vertices)
{
	NumIndices = Indices.size();
	//将顶点数据（包含vertex,texturecoord,normals）放入缓冲区
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
	//将顶点索引放入缓冲区
	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);

	////将顶点数据(包含vertex三维坐标）放入缓冲区
	//glGenBuffers(1, &vertexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
}


bool objMesh::loadObj(const std::string & filename)
{
	printf("Loading OBJ file %s...\n", filename);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(filename.c_str(), "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	return true;
}

bool objMesh::loadAssImp(const std::string & path)
{
	Assimp::Importer importer;
	bool Ret = false;
	const aiScene* scene = importer.ReadFile(path, 0/*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
	if (!scene) {
		fprintf(stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	if (scene) {
		Ret = InitFromScene(scene, path);
	}
	else {
		printf("Error parsing '%s': '%s'\n", path.c_str(), importer.GetErrorString());
	}

	return Ret;
}

bool objMesh::InitFromScene(const aiScene * pScene, const std::string & Filename)
{
	m_Entries.resize(pScene->mNumMeshes);
	m_Textures.resize(pScene->mNumMaterials);

	// Initialize the meshes in the scene one by one
	//有m_Entries.size()个网格，遍历每个网格，进行初始化
	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		//对第i个网格进行初始化
		InitMesh(i, paiMesh);
	}
	//初始化材质纹理信息等
	return InitMaterials(pScene, Filename);
}
void objMesh::InitMesh(unsigned int Index, const aiMesh * paiMesh)
{

	m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
		glm::vec3 v(pPos->x, pPos->y, pPos->z);
		glm::vec2 t(pTexCoord->x, pTexCoord->y);
		glm::vec3 n(pNormal->x, pNormal->y, pNormal->z);
		vertices.push_back(v);
		texturecoods.push_back(t);
		normals.push_back(n);

		Vertex tem(v,t,n);
		Vertices.push_back(tem);
	}

	//只能读取类似 f 1/2/3 2/3/4 6/2/1 类型的obj文件。不能读取f 1//2 2//4 4//8类型的obj文件
	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];

		for (GLuint j = 0; j < Face.mNumIndices; j++)
			Indices.push_back(Face.mIndices[j]);
		//assert(Face.mNumIndices == 3);
		if (Face.mNumIndices == 3) {
			Indices.push_back(Face.mIndices[0]);
			Indices.push_back(Face.mIndices[1]);
			Indices.push_back(Face.mIndices[2]);
		}
		else if (Face.mNumIndices == 4)
		{
			Indices.push_back(Face.mIndices[0]);
			Indices.push_back(Face.mIndices[1]);
			Indices.push_back(Face.mIndices[2]);
			Indices.push_back(Face.mIndices[3]);
		}
	}

	m_Entries[Index].Init(Vertices, Indices,vertices);
}
bool objMesh::InitMaterials(const aiScene * pScene, const std::string & Filename)
{
	// Extract the directory part from the file name
	std::string::size_type SlashIndex = Filename.find_last_of("/");
	std::string Dir;

	if (SlashIndex == std::string::npos) {
		Dir = ".";
	}
	else if (SlashIndex == 0) {
		Dir = "/";
	}
	else {
		Dir = Filename.substr(0, SlashIndex);
	}

	bool Ret = true;

	// Initialize the materials
	for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		m_Textures[i] = NULL;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				std::string FullPath = Dir + "/" + Path.data;
				m_Textures[i] = new texture(GL_TEXTURE_2D, FullPath.c_str());

				if (!m_Textures[i]->load()) {
					printf("Error loading texture '%s'\n", FullPath.c_str());
					delete m_Textures[i];
					m_Textures[i] = NULL;
					Ret = false;
				}
				else {
					printf("Loaded texture '%s'\n", FullPath.c_str());
				}
			}
		}

		// Load a white texture in case the model does not include its own texture
		if (!m_Textures[i]) {
			m_Textures[i] = new texture(GL_TEXTURE_2D, "Content/white.png");

			Ret = m_Textures[i]->load();
		}
	}

	return Ret;
}


void objMesh::render(int renderMode) {
	if (renderMode == OBJMESHRENDER_TEXTURE)
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		for (unsigned int i = 0; i < m_Entries.size(); i++) {
			glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

			const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

			if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
				m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
			}

			glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
	else if (renderMode == OBJMESHRENDER_TRIANGLE)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//只显示三角网格
		glEnableVertexAttribArray(0);
		//获取网格顶点
		
		for (unsigned int i = 0; i < m_Entries.size(); i++) {
			glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);
			glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
		}
		glDisableVertexAttribArray(0);
			
	}
	else if (renderMode == OBJMESHRENDER_VERTEX)
	{	glEnable(GL_DEPTH_TEST);
	//Acepte the front fragment
	glEnable(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

		//只显示顶点
		glEnableVertexAttribArray(0);
		//获取网格顶点
		for (unsigned int i = 0; i < m_Entries.size(); i++) {
			glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);
			glDrawElements(GL_POINTS, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_POINTS, 0, 3);
		}
		glDisableVertexAttribArray(0);
	}
}

objMesh::MeshEntry::MeshEntry()
{
	VB = INVALID_OGL_VALUE;
	IB = INVALID_OGL_VALUE;
	NumIndices = 0;
	MaterialIndex = INVALID_MATERIAL;
}

objMesh::MeshEntry::~MeshEntry()
{
	if (VB != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &VB);
	}

	if (IB != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &IB);
	}
}


