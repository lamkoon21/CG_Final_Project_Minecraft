#ifndef TEXTURE_H
#define TEXTURE_H


#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <string>
#include <map>


extern std::map<std::string, unsigned int> textures;


void UseTexture(const char* key);
void EnterTexture();
void SetTexture(const char* filename, unsigned int& texture);
void InsertTexture(const char* key, const char* filename);


#endif