#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H


#include "../objreader/objRead.h"


class CharacterData
{
public:
	GLuint VAO_head, VAO_body, VAO_left_arm, VAO_right_arm, VAO_left_leg, VAO_right_leg;
	objRead characterReader[6];
	GLint HeadObj = characterReader[0].loadObj_normalize_center("resource/obj/character/character_head.obj");
	GLint BodyObj = characterReader[1].loadObj_normalize_center("resource/obj/character/character_body.obj");
	GLint LeftArmObj = characterReader[2].loadObj_normalize_center("resource/obj/character/character_left_arm.obj");
	GLint RightArmObj = characterReader[3].loadObj_normalize_center("resource/obj/character/character_right_arm.obj");
	GLint LeftLegObj = characterReader[4].loadObj_normalize_center("resource/obj/character/character_left_leg.obj");
	GLint RightLegObj = characterReader[5].loadObj_normalize_center("resource/obj/character/character_right_leg.obj");
	

	const float CHARACTER_SPEED[3] = { 0.08f, 0.12f, 0.04f };
	const float MAX_SHAKE_DEG[3] = { 20.0f, 40.0f, 15.0f };
	const float ADD_SHAKE_DEG[3] = { 2.0f, 4.0f, 1.5f };


	CharacterData()
	{
		characterReader[0].initBuffer(VAO_head);
		characterReader[1].initBuffer(VAO_body);
		characterReader[2].initBuffer(VAO_left_arm);
		characterReader[3].initBuffer(VAO_right_arm);
		characterReader[4].initBuffer(VAO_left_leg);
		characterReader[5].initBuffer(VAO_right_leg);
	}
};


#endif