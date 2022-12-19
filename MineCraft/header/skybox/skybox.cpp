#include "skybox.h"


void Skybox::Init()
{
	skyboxReader.initBuffer(VAO);
}

void Skybox::Render()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, SkyboxObj);
}
