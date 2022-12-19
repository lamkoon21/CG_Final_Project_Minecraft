#ifndef PAUSE_H
#define PAUSE_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <Windows.h>
#include <map>
#include "../shader/shader.h"
#include "../stb_image/stb_image.h"

float pause_background[] = {
	// 위치               // 컬러             // 텍스처 좌표
	1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.05f, 0.05f,   // 우측 상단
	1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.05f, 0.0f,    // 우측 하단
   -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,     // 좌측 하단
   -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.05f     // 좌측 상단
};

float gamemenu[] = {
	// 위치                 // 컬러             // 텍스처 좌표
	0.45f,  0.65f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.45f,   // 우측 상단
	0.45f,  0.49f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.4f,    // 우측 하단
   -0.45f,  0.49f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.4f,    // 좌측 하단
   -0.45f,  0.65f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.45f    // 좌측 상단
};

float backtogame[] = {
	// 위치                  // 컬러             // 텍스처 좌표
	0.45f,  0.35f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.4f,    // 우측 상단
	0.45f,  0.19f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.35f,   // 우측 하단
   -0.45f,  0.19f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.35f,   // 좌측 하단
   -0.45f,  0.35f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.4f     // 좌측 상단
};

float back_button[] = {
	// 위치                 // 컬러             // 텍스처 좌표
	0.45f,  0.35f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.95f,   // 우측 상단
	0.45f,  0.19f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.9f,    // 우측 하단
   -0.45f,  0.19f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.9f,    // 좌측 하단
   -0.45f,  0.35f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.95f    // 좌측 상단
};

float back_button_activate[] = {
	// 위치                 // 컬러             // 텍스처 좌표
	0.45f,  0.35f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.9f,    // 우측 상단
	0.45f,  0.19f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.85f,   // 우측 하단
   -0.45f,  0.19f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.85f,   // 좌측 하단
   -0.45f,  0.35f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.9f     // 좌측 상단
};

float advancements[] = {
	// 위치                  // 컬러             // 텍스처 좌표
	0.22f,   0.15f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.35f,   // 우측 상단
	0.22f,  -0.01f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.3f,    // 우측 하단
   -0.68f,  -0.01f, 0.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.3f,    // 좌측 하단
   -0.68f,   0.15f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 0.35f    // 좌측 상단
};

float advance_button[] = {
	// 위치                    // 컬러             // 텍스처 좌표
   -0.012f,   0.15f, 0.0f,   1.0f, 0.0f, 0.0f,   0.475f, 0.85f,   // 우측 상단
   -0.012f,   -0.01f, 0.0f,   0.0f, 1.0f, 0.0f,  0.475f, 0.8f,    // 우측 하단
   -0.45f,   -0.01f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.8f,      // 좌측 하단
   -0.45f,    0.15f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.85f      // 좌측 상단
};

float statistics[] = {
	// 위치                  // 컬러             // 텍스처 좌표
	0.68f,   0.15f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.3f,     // 우측 상단
	0.68f,  -0.01f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.25f,    // 우측 하단
   -0.22f,  -0.01f, 0.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.25f,    // 좌측 하단
   -0.22f,   0.15f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 0.3f      // 좌측 상단
};

float stat_button[] = {
	// 위치                    // 컬러             // 텍스처 좌표
	0.45f,     0.15f, 0.0f,   1.0f, 0.0f, 0.0f,   0.475f, 0.85f,   // 우측 상단
	0.45f,    -0.01f, 0.0f,   0.0f, 1.0f, 0.0f,   0.475f, 0.8f,    // 우측 하단
	0.012f,   -0.01f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.8f,      // 좌측 하단
	0.012f,    0.15f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.85f      // 좌측 상단
};

float pause_options[] = {
	// 위치                  // 컬러             // 텍스처 좌표
	0.22f,   -0.25f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.25f,   // 우측 상단
	0.22f,   -0.41f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.2f,    // 우측 하단
   -0.68f,   -0.41f, 0.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.2f,    // 좌측 하단
   -0.68f,   -0.25f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 0.25f    // 좌측 상단
};

float pause_options_button[] = {
	// 위치                    // 컬러             // 텍스처 좌표
   -0.012f,  -0.25f, 0.0f,   1.0f, 0.0f, 0.0f,   0.475f, 0.85f,   // 우측 상단
   -0.012f,  -0.41f, 0.0f,   0.0f, 1.0f, 0.0f,   0.475f, 0.8f,    // 우측 하단
   -0.45f,   -0.41f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.8f,      // 좌측 하단
   -0.45f,   -0.25f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.85f      // 좌측 상단
};

float opentolan[] = {
	// 위치                  // 컬러             // 텍스처 좌표
	0.68f,   -0.25f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.2f,     // 우측 상단
	0.68f,   -0.41f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.15f,    // 우측 하단
   -0.22f,   -0.41f, 0.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.15f,    // 좌측 하단
   -0.22f,   -0.25f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 0.2f      // 좌측 상단
};

float opentolan_button[] = {
	// 위치                    // 컬러             // 텍스처 좌표
	0.45f,   -0.25f, 0.0f,   1.0f, 0.0f, 0.0f,   0.475f, 0.85f,   // 우측 상단
	0.45f,   -0.41f, 0.0f,   0.0f, 1.0f, 0.0f,   0.475f, 0.8f,    // 우측 하단
	0.012f,  -0.41f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.8f,      // 좌측 하단
	0.01f,  -0.25f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.85f      // 좌측 상단
};

float quittotitle[] = {
	// 위치                  // 컬러             // 텍스처 좌표
	0.45f,  -0.45f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.15f,    // 우측 상단
	0.45f,  -0.61f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.1f,   // 우측 하단
   -0.45f,  -0.61f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.1f,   // 좌측 하단
   -0.45f,  -0.45f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.15f     // 좌측 상단
};

float quittotitle_button[] = {
	// 위치                 // 컬러             // 텍스처 좌표
	0.45f,  -0.45f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.95f,   // 우측 상단
	0.45f,  -0.61f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.9f,    // 우측 하단
   -0.45f,  -0.61f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.9f,    // 좌측 하단
   -0.45f,  -0.45f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.95f    // 좌측 상단
};

float quittotitle_button_activate[] = {
	// 위치                 // 컬러             // 텍스처 좌표
	0.45f,  -0.45f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.9f,    // 우측 상단
	0.45f,  -0.61f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.85f,   // 우측 하단
   -0.45f,  -0.61f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.85f,   // 좌측 하단
   -0.45f,  -0.45f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.9f     // 좌측 상단
};

GLuint VAO_pause_background;
GLuint VAO_pause_button[8];
GLuint VAO_pause_words[7];

GLuint VBO_pause_background;
GLuint VBO_pause_button[8];
GLuint VBO_pause_words[7];

GLuint EBO_pause_background;
GLuint EBO_pause_button[8];
GLuint EBO_pause_words[7];

std::map<std::string, unsigned int> pause_textures = { };

class Pause
{
public:
	Shader pauseShader;

	void Init()
	{
		//background
		glGenVertexArrays(1, &VAO_pause_background);
		glGenBuffers(1, &VBO_pause_background);
		glGenBuffers(1, &EBO_pause_background);

		glBindVertexArray(VAO_pause_background);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_pause_background);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pause_background), pause_background, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_pause_background);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);




		//ui
		for (int i = 0; i < 8; ++i)
		{
			//button
			glGenVertexArrays(1, &VAO_pause_button[i]);
			glGenBuffers(1, &VBO_pause_button[i]);
			glGenBuffers(1, &EBO_pause_button[i]);

			glBindVertexArray(VAO_pause_button[i]);

			glBindBuffer(GL_ARRAY_BUFFER, VBO_pause_button[i]);

			switch (i)
			{
			case 0:
				glBufferData(GL_ARRAY_BUFFER, sizeof(back_button), back_button, GL_STATIC_DRAW);
				break;
			case 1:
				glBufferData(GL_ARRAY_BUFFER, sizeof(advance_button), advance_button, GL_STATIC_DRAW);
				break;
			case 2:
				glBufferData(GL_ARRAY_BUFFER, sizeof(stat_button), stat_button, GL_STATIC_DRAW);
				break;
			case 3:
				glBufferData(GL_ARRAY_BUFFER, sizeof(pause_options_button), pause_options_button, GL_STATIC_DRAW);
				break;
			case 4:
				glBufferData(GL_ARRAY_BUFFER, sizeof(opentolan_button), opentolan_button, GL_STATIC_DRAW);
				break;
			case 5:
				glBufferData(GL_ARRAY_BUFFER, sizeof(quittotitle_button), quittotitle_button, GL_STATIC_DRAW);
				break;
			case 6:
				glBufferData(GL_ARRAY_BUFFER, sizeof(back_button_activate), back_button_activate, GL_STATIC_DRAW);
				break;
			case 7:
				glBufferData(GL_ARRAY_BUFFER, sizeof(quittotitle_button_activate), quittotitle_button_activate, GL_STATIC_DRAW);
				break;
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_pause_button[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// color attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// texture coord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);

			if (i > 6)continue;

			//words
			glGenVertexArrays(1, &VAO_pause_words[i]);
			glGenBuffers(1, &VBO_pause_words[i]);
			glGenBuffers(1, &EBO_pause_words[i]);

			glBindVertexArray(VAO_pause_words[i]);

			glBindBuffer(GL_ARRAY_BUFFER, VBO_pause_words[i]);

			switch (i)
			{
			case 0:
				glBufferData(GL_ARRAY_BUFFER, sizeof(backtogame), backtogame, GL_STATIC_DRAW);
				break;
			case 1:
				glBufferData(GL_ARRAY_BUFFER, sizeof(advancements), advancements, GL_STATIC_DRAW);
				break;
			case 2:
				glBufferData(GL_ARRAY_BUFFER, sizeof(statistics), statistics, GL_STATIC_DRAW);
				break;
			case 3:
				glBufferData(GL_ARRAY_BUFFER, sizeof(pause_options), pause_options, GL_STATIC_DRAW);
				break;
			case 4:
				glBufferData(GL_ARRAY_BUFFER, sizeof(opentolan), opentolan, GL_STATIC_DRAW);
				break;
			case 5:
				glBufferData(GL_ARRAY_BUFFER, sizeof(quittotitle), quittotitle, GL_STATIC_DRAW);
				break;
			case 6:
				glBufferData(GL_ARRAY_BUFFER, sizeof(gamemenu), gamemenu, GL_STATIC_DRAW);
				break;
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_pause_words[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// color attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// texture coord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);

		}


	}

	void render_pause()
	{
		pauseShader.setShader("shader/vertex_title.glsl", "shader/fragment_title.glsl");
		pauseShader.use();

		UseTexture_pause("pause_background");
		glBindVertexArray(VAO_pause_background);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		UseTexture_pause("pause_button");
		for (int i = 0; i < 6; ++i)
		{
			if (i == 0 && select_pause_menu == 1)
				glBindVertexArray(VAO_pause_button[6]);
			else if (i == 5 && select_pause_menu == -1)
				glBindVertexArray(VAO_pause_button[7]);
			else
				glBindVertexArray(VAO_pause_button[i]);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glBindVertexArray(VAO_pause_words[i]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		glBindVertexArray(VAO_pause_words[6]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void UseTexture_pause(const char* key)
	{
		if (pause_textures.find(key) != pause_textures.end()) {
			glBindTexture(GL_TEXTURE_2D, pause_textures[key]);
		}
		else {
			std::cerr << "ERROR! Can't use undefined key\n";
		}
	}

	void EnterTexture_pause()
	{
		pause_textures.clear();
		// pause tex
		InsertTexture_pause("pause_background", "resource/texture/ui/title_pause_ui.png");
		// ui tex
		InsertTexture_pause("pause_button", "resource/texture/ui/title_pause_ui.png");
	}

	void SetTexture_pause(const char* filename, unsigned int& texture)
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

	void InsertTexture_pause(const char* key, const char* filename)
	{
		if (pause_textures.find(key) != pause_textures.end()) {
			std::cerr << "ERROR! Duplicate texture key can\'t be used\n";
		}
		else {
			unsigned int texture;
			SetTexture_pause(filename, texture);
			pause_textures.insert({ key, texture });
		}
	}

	int select_pause_menu = 0;
	bool go_to_pause = false;
	bool go_to_title = false;
	bool escape = false;

	//#include "pause.h"

	void Input_keyboard(unsigned char key)
	{
		switch (key)
		{
		case 27: // ESCAPE
			if (escape)
			{
				go_to_pause = false;
				escape = false;
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_CULL_FACE);
			}
			else
			{
				escape = true;
			}
			break;
		case 13: // ENTER
			if (select_pause_menu)
			{
				go_to_pause = false;
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_CULL_FACE);
			}
			else
			{
				select_pause_menu = 0;
				go_to_pause = false;
				escape = false;
				go_to_title = true;
			}
			break;

		case GLUT_KEY_UP:
			if (select_pause_menu == 0)
				select_pause_menu = 1;
			else
				select_pause_menu *= -1;
			break;

		case GLUT_KEY_DOWN:
			if (select_pause_menu == 0)
				select_pause_menu = -1;
			else
				select_pause_menu *= -1;
			break;
		}
	}

	void Input_mouse(int button, int state, float x, float y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{

			//start button
			if (-0.45f < x && x < 0.45f && 0.19f < y && y < 0.35f)
			{
				select_pause_menu = true;
				go_to_pause = false;
				escape = false;
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_CULL_FACE);
			}

			//quit button
			if (-0.45f < x && x < 0.45f && -0.61f < y && y < -0.45f)
			{
				select_pause_menu = 0;
				go_to_pause = false;
				escape = false;
				go_to_title = true;
			}
		}

	}

	void Input_motion(float x, float y)
	{
		//start button
		if (-0.45f < x && x < 0.45f && 0.19f < y && y < 0.35f)
		{
			select_pause_menu = 1;
		}

		//quit button
		else if (-0.45f < x && x < 0.45f && -0.61f < y && y < -0.45f)
		{
			select_pause_menu = -1;
		}

		else
		{
			select_pause_menu = 0;
		}
	}

};


#endif