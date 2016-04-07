#pragma once
#ifndef _TEXTURE_H
#define _TEXTURE_H
#pragma warning(disable:4996)
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/common.hpp>
#include <GL/FreeImage.h>

class texture {
public:
	texture(GLenum TextureTarget, const std::string& FileName);
	~texture() { glDeleteTextures(1, &Texture); };

	//DDS ��ʽ����ͼƬ
	bool loadDDS();
	//BMP ��ʽ����ͼƬ
	bool loadBMP();
	//����freeimage��������ͼƬ
	bool load();
	void set(GLuint pId);
	void Bind(GLenum TextureUnit);



private:
	std::string m_fileName;
	GLenum m_textureTarget;
	GLuint m_textureObj;
	GLuint Texture;
	GLuint TextureID;

};
#endif // !_TEXTURE_H
