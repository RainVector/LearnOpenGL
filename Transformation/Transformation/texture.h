#ifndef  TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/FreeImage.h>
#include <string>

class Texture
{
public:
	Texture();
	void loadTexture(const std::string &file);
	void loadTexture(const std::string &file, GLenum TextureTarget);
	void Bind();
	void Bind(GLenum TextureTarget);

	~Texture();

private:
	GLuint textureID;

};

Texture::Texture()
{
}

/*
* ��������
*/
inline void Texture::loadTexture(const std::string &file)
{
	//����ͼƬ
	try
	{
		FIBITMAP* bitmap = FreeImage_Load(
			FreeImage_GetFileType(file.c_str(), 0),
			file.c_str());
		FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
		int Width = FreeImage_GetWidth(pImage);
		int Height = FreeImage_GetHeight(pImage);
		//����1������
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		//���������뻺����
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

		//�������������
		glGenerateMipmap(GL_TEXTURE_2D);
		//���������Ʒ�ʽ
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//���textureID
		glBindTexture(GL_TEXTURE_2D, 0);
		//�ͷ�ͼ���ڴ�
		FreeImage_Unload(pImage);
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception" << e.what() << std::endl;
	}

}

inline void Texture::loadTexture(const std::string & file, GLenum TextureTarget)
{
	//����ͼƬ
	try
	{
		FIBITMAP* bitmap = FreeImage_Load(
			FreeImage_GetFileType(file.c_str(), 0),
			file.c_str());
		FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
		int Width = FreeImage_GetWidth(pImage);
		int Height = FreeImage_GetHeight(pImage);
		//����1������
		glGenTextures(1, &textureID);
		glBindTexture(TextureTarget, textureID);
		//���������뻺����
		glTexImage2D(TextureTarget, 0, GL_RGBA8, Width, Height,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

		//�������������
		glGenerateMipmap(TextureTarget);
		//���������Ʒ�ʽ
		glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//���textureID
		glBindTexture(TextureTarget, 0);
		//�ͷ�ͼ���ڴ�
		FreeImage_Unload(pImage);
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception" << e.what() << std::endl;
	}
}

inline void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

inline void Texture::Bind(GLenum TextureTarget)
{
	glBindTexture(TextureTarget, textureID);
}

Texture::~Texture()
{
}
#endif // ! TEXTURE_H
