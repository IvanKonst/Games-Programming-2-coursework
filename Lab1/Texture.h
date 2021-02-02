#pragma once
#include <string>
#include <GL\glew.h>

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind(unsigned int unit); // bind upto 32 textures
	void InitTexture(const std::string& fileName);

	~Texture();

protected:
private:

	GLuint textureHandler;
};

