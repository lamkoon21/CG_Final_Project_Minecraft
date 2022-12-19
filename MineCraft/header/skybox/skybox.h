#ifndef SKYBOX_H
#define SKYBOX_H


#include "GL/glew.h"
#include "../objreader/objRead.h"


class Skybox
{
	GLuint VAO;
	objRead skyboxReader;
	GLint SkyboxObj = skyboxReader.loadObj_normalize_center("resource/obj/skybox.obj");
public:
	void Init();
	void Render();
};


#endif