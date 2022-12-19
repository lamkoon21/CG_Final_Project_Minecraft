#ifndef TRANSFORM_H
#define TRANSFORM_H


#include "glm/glm.hpp"
#include "../shader/shader.h"


void SRT(glm::vec3 scale, glm::vec3 rotate, glm::vec3 pos, Shader *shader);
void SRTR(glm::vec3 scale, glm::vec3 rotate1, glm::vec3 pos, glm::vec3 rotate2, Shader *shader);


void SRT(glm::vec3 scale, glm::vec3 rotate, glm::vec3 pos, Shader *shader)
{
	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Sc = glm::mat4(1.0f);

	Sc = glm::scale(Sc, glm::vec3(scale.x, scale.y, scale.z));
	Rz *= glm::rotate(Rz, rotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
	Rz *= glm::rotate(Rz, rotate.y / 2, glm::vec3(0.0f, 1.0f, 0.0f));
	Rz *= glm::rotate(Rz, rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
	Tx = glm::translate(Tx, pos);

	TR = Tx * Rz * Sc;
	shader->setMat4("model", TR);
}


void SRTR(glm::vec3 scale, glm::vec3 rotate1, glm::vec3 pos, glm::vec3 rotate2, Shader *shader)
{
	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Rz1 = glm::mat4(1.0f);
	glm::mat4 Rz2 = glm::mat4(1.0f);
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Sc = glm::mat4(1.0f);

	Sc = glm::scale(Sc, glm::vec3(scale.x, scale.y, scale.z));
	Rz1 *= glm::rotate(Rz1, rotate1.x, glm::vec3(1.0f, 0.0f, 0.0f));
	Rz1 *= glm::rotate(Rz1, rotate1.y, glm::vec3(0.0f, 1.0f, 0.0f));
	Rz1 *= glm::rotate(Rz1, rotate1.z, glm::vec3(0.0f, 0.0f, 1.0f));
	Tx = glm::translate(Tx, pos);
	Rz2 *= glm::rotate(Rz2, rotate2.x, glm::vec3(1.0f, 0.0f, 0.0f));
	Rz2 *= glm::rotate(Rz2, rotate2.y, glm::vec3(0.0f, 1.0f, 0.0f));
	Rz2 *= glm::rotate(Rz2, rotate2.z, glm::vec3(0.0f, 0.0f, 1.0f));

	TR = Rz2 * Tx * Rz1 * Sc;
	shader->setMat4("model", TR);
}


void STRT(glm::vec3 scale, glm::vec3 pos1, glm::vec3 rotate1, glm::vec3 pos2, Shader* shader)
{
	glm::mat4 Tx1 = glm::mat4(1.0f);
	glm::mat4 Tx2 = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 Sc = glm::mat4(1.0f);
	glm::mat4 TR = glm::mat4(1.0f);

	Sc = glm::scale(Sc, glm::vec3(scale.x, scale.y, scale.z));
	Rz *= glm::rotate(Rz, rotate1.x, glm::vec3(1.0f, 0.0f, 0.0f));
	Rz *= glm::rotate(Rz, rotate1.y, glm::vec3(0.0f, 1.0f, 0.0f));
	Rz *= glm::rotate(Rz, rotate1.z, glm::vec3(0.0f, 0.0f, 1.0f));
	Tx1 = glm::translate(Tx1, pos1);
	Tx2 = glm::translate(Tx2, pos2);

	TR = Tx2 * Rz * Tx1 * Sc;
	shader->setMat4("model", TR);
}


#endif