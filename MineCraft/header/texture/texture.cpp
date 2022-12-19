#include "texture.h"


#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"


std::map<std::string, unsigned int> textures = { };


void UseTexture(const char* key)
{
	if (textures.find(key) != textures.end()) {
		glBindTexture(GL_TEXTURE_2D, textures[key]);
	}
	else {
		std::cerr << "ERROR! Can't use undefined key\n";
	}
}

void EnterTexture()
{
	textures.clear();

	InsertTexture("test", "resource/texture/block/test.png");

	InsertTexture("block_atlas", "resource/texture/block/block_atlas.png");
	InsertTexture("character", "resource/texture/character.png");
	InsertTexture("skybox", "resource/texture/skybox.png");
	InsertTexture("item_ui", "resource/texture/ui/item_ui.png");
	InsertTexture("select_item_ui", "resource/texture/ui/selecte_item_ui.png");
}

void SetTexture(const char* filename, unsigned int& texture)
{
	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << filename << " Failed to load texture\n" << std::endl;
	}
	stbi_image_free(data);
}

void InsertTexture(const char* key, const char* filename)
{
	if (textures.find(key) != textures.end()) {
		std::cerr << "ERROR! Duplicate texture key can\'t be used\n";
	}
	else {
		unsigned int texture;
		SetTexture(filename, texture);
		textures.insert({ key, texture });
	}
}

