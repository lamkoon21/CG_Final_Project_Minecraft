#ifndef TITLE_H
#define TITLE_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <Windows.h>
#include <map>
#include "../shader/shader.h"
#include "../stb_image/stb_image.h"

float background[] = {
	// 위치              // 컬러             // 텍스처 좌표
	1.2f,  1.2f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 우측 상단
	1.2f, -2.4f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 우측 하단
   -1.2f, -2.4f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 좌측 하단
   -1.2f,  1.2f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 좌측 상단
};

float title_name[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.607f,  0.74f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 우측 상단
	0.607f,  0.39f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 우측 하단
   -0.625f,  0.39f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 좌측 하단
   -0.625f,  0.74f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 좌측 상단
};

float singleplayer[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.45f,  0.1f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.7f,   // 우측 상단
	0.45f,  -0.06f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.65f,   // 우측 하단
   -0.45f,  -0.06f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.65f,   // 좌측 하단
   -0.45f,  0.1f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.7f    // 좌측 상단
};

float single_button[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.45f,  0.1f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.95f,   // 우측 상단
	0.45f,  -0.06f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.9f,   // 우측 하단
   -0.45f,  -0.06f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.9f,   // 좌측 하단
   -0.45f,  0.1f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.95f    // 좌측 상단
};

float single_button_activate[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.45f,  0.1f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.9f,   // 우측 상단
	0.45f,  -0.06f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.85f,   // 우측 하단
   -0.45f,  -0.06f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.85f,   // 좌측 하단
   -0.45f,  0.1f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.9f    // 좌측 상단
};

float multiplayer[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.45f,  -0.09f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.65f,   // 우측 상단
	0.45f,  -0.25f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.6f,   // 우측 하단
   -0.45f,  -0.25f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.6f,   // 좌측 하단
   -0.45f,  -0.09f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.65f    // 좌측 상단
};

float multi_button[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.45f,  -0.09f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 우측 상단
	0.45f,  -0.25f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.95f,   // 우측 하단
   -0.45f,  -0.25f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.95f,   // 좌측 하단
   -0.45f,  -0.09f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 좌측 상단
};

float mods[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.45f,  -0.28f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.6f,   // 우측 상단
	0.45f,  -0.45f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.55f,   // 우측 하단
   -0.45f,  -0.45f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.55f,   // 좌측 하단
   -0.45f,  -0.28f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.6f    // 좌측 상단
};

float mods_button[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.45f,  -0.28f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 우측 상단
	0.45f,  -0.441f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.95f,   // 우측 하단
   -0.45f,  -0.441f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.95f,   // 좌측 하단
   -0.45f,  -0.28f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 좌측 상단
};

float options[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.22f,  -0.58f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.55f,   // 우측 상단
	0.22f,  -0.74f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.5f,   // 우측 하단
   -0.68f,  -0.74f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.5f,   // 좌측 하단
   -0.68f,  -0.58f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.55f    // 좌측 상단
};

float options_button[] = {
	// 위치              // 컬러             // 텍스처 좌표
	-0.013f,  -0.57f, 0.0f,    1.0f, 0.0f, 0.0f,   0.475f, 0.85f,   // 우측 상단
	-0.013f,  -0.73f, 0.0f,   0.0f, 1.0f, 0.0f,   0.475f, 0.8f,   // 우측 하단
	-0.45f,  -0.73f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.8f,   // 좌측 하단
	-0.45f,  -0.57f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 0.85f    // 좌측 상단
};

float quitgame[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.69f,  -0.58f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.5f,   // 우측 상단
	0.69f,  -0.74f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.45f,   // 우측 하단
   -0.21f,  -0.74f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.45f,   // 좌측 하단
   -0.21f,  -0.58f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.5f    // 좌측 상단
};

float quit_button[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.45f,  -0.57f, 0.0f,    1.0f, 0.0f, 0.0f,   0.475f, 0.8f,   // 우측 상단
	0.45f,  -0.73f, 0.0f,   0.0f, 1.0f, 0.0f,   0.475f, 0.75f,   // 우측 하단
	0.013f,   -0.73f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.75f,   // 좌측 하단
	0.013f,   -0.57f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 0.8f    // 좌측 상단
};

float quit_button_activate[] = {
	// 위치              // 컬러             // 텍스처 좌표
	0.45f,  -0.57f, 0.0f,    1.0f, 0.0f, 0.0f,   0.475f, 0.75f,   // 우측 상단
	0.45f,  -0.73f, 0.0f,   0.0f, 1.0f, 0.0f,   0.475f, 0.7f,   // 우측 하단
	0.013f,   -0.73f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.7f,   // 좌측 하단
	0.013f,   -0.57f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 0.75f    // 좌측 상단
};

unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
};

GLuint VAO_background;
GLuint VAO_title_name;
GLuint VAO_button[7];
GLuint VAO_words[5];

GLuint VBO_background;
GLuint VBO_title_name;
GLuint VBO_button[7];
GLuint VBO_words[5];

GLuint EBO_background;
GLuint EBO_title_name;
GLuint EBO_button[7];
GLuint EBO_words[5];

std::map<std::string, unsigned int> title_textures = { };

class Title
{
public:
	Shader titleShader;

	void Init()
	{
		//background
		glGenVertexArrays(1, &VAO_background);
		glGenBuffers(1, &VBO_background);
		glGenBuffers(1, &EBO_background);

		glBindVertexArray(VAO_background);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_background);
		glBufferData(GL_ARRAY_BUFFER, sizeof(background), background, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_background);
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


		//title_name
		glGenVertexArrays(1, &VAO_title_name);
		glGenBuffers(1, &VBO_title_name);
		glGenBuffers(1, &EBO_title_name);

		glBindVertexArray(VAO_title_name);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_title_name);
		glBufferData(GL_ARRAY_BUFFER, sizeof(title_name), title_name, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_title_name);
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
		for (int i = 0; i < 7; ++i)
		{
			//button
			glGenVertexArrays(1, &VAO_button[i]);
			glGenBuffers(1, &VBO_button[i]);
			glGenBuffers(1, &EBO_button[i]);

			glBindVertexArray(VAO_button[i]);

			glBindBuffer(GL_ARRAY_BUFFER, VBO_button[i]);

			switch (i)
			{
			case 0:
				glBufferData(GL_ARRAY_BUFFER, sizeof(single_button), single_button, GL_STATIC_DRAW);
				break;
			case 1:
				glBufferData(GL_ARRAY_BUFFER, sizeof(multi_button), multi_button, GL_STATIC_DRAW);
				break;
			case 2:
				glBufferData(GL_ARRAY_BUFFER, sizeof(mods_button), mods_button, GL_STATIC_DRAW);

				break;
			case 3:
				glBufferData(GL_ARRAY_BUFFER, sizeof(options_button), options_button, GL_STATIC_DRAW);

				break;
			case 4:
				glBufferData(GL_ARRAY_BUFFER, sizeof(quit_button), quit_button, GL_STATIC_DRAW);
				break;
			case 5:
				glBufferData(GL_ARRAY_BUFFER, sizeof(single_button_activate), single_button_activate, GL_STATIC_DRAW);

				break;
			case 6:
				glBufferData(GL_ARRAY_BUFFER, sizeof(quit_button_activate), quit_button_activate, GL_STATIC_DRAW);
				break;
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_button[i]);
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

			if (i > 4)continue;

			//words
			glGenVertexArrays(1, &VAO_words[i]);
			glGenBuffers(1, &VBO_words[i]);
			glGenBuffers(1, &EBO_words[i]);

			glBindVertexArray(VAO_words[i]);

			glBindBuffer(GL_ARRAY_BUFFER, VBO_words[i]);

			switch (i)
			{
			case 0:
				glBufferData(GL_ARRAY_BUFFER, sizeof(singleplayer), singleplayer, GL_STATIC_DRAW);
				break;
			case 1:
				glBufferData(GL_ARRAY_BUFFER, sizeof(multiplayer), multiplayer, GL_STATIC_DRAW);
				break;
			case 2:
				glBufferData(GL_ARRAY_BUFFER, sizeof(mods), mods, GL_STATIC_DRAW);
				break;
			case 3:
				glBufferData(GL_ARRAY_BUFFER, sizeof(options), options, GL_STATIC_DRAW);
				break;
			case 4:
				glBufferData(GL_ARRAY_BUFFER, sizeof(quitgame), quitgame, GL_STATIC_DRAW);
				break;
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_words[i]);
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

	void render_title()
	{
		titleShader.setShader("shader/vertex_title.glsl", "shader/fragment_title.glsl");
		titleShader.use();

		UseTexture_title("background");
		glBindVertexArray(VAO_background);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		UseTexture_title("title_name");
		glBindVertexArray(VAO_title_name);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		UseTexture_title("button");
		for (int i = 0; i < 5; ++i)
		{
			if (i == 0 && select_menu == 1)
				glBindVertexArray(VAO_button[5]);
			else if (i == 4 && select_menu == -1)
				glBindVertexArray(VAO_button[6]);
			else
				glBindVertexArray(VAO_button[i]);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glBindVertexArray(VAO_words[i]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}


	}

	void UseTexture_title(const char* key)
	{
		if (title_textures.find(key) != title_textures.end()) {
			glBindTexture(GL_TEXTURE_2D, title_textures[key]);
		}
		else {
			std::cerr << "ERROR! Can't use undefined key\n";
		}
	}

	void EnterTexture_title()
	{
		title_textures.clear();
		// title tex
		InsertTexture_title("background", "resource/texture/title/background.png");
		InsertTexture_title("title_name", "resource/texture/title/title_name.png");
		// ui tex
		InsertTexture_title("button", "resource/texture/ui/title_pause_ui.png");
	}

	void SetTexture_title(const char* filename, unsigned int& texture)
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

	void InsertTexture_title(const char* key, const char* filename)
	{
		if (title_textures.find(key) != title_textures.end()) {
			std::cerr << "ERROR! Duplicate texture key can\'t be used\n";
		}
		else {
			unsigned int texture;
			SetTexture_title(filename, texture);
			title_textures.insert({ key, texture });
		}
	}

	int select_menu = 0;
	bool game_start = false;

	void Input_keyboard(unsigned char key)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
			if (select_menu == 0)
				select_menu = 1;
			else
				select_menu *= -1;
			break;
		case GLUT_KEY_DOWN:
			if (select_menu == 0)
				select_menu = -1;
			else
				select_menu *= -1;
			break;
		case 13: // ENTER
			if (select_menu)
			{
				game_start = true;
				select_menu = 0;
			}
			else
				exit(0);
			break;
		}
	}



	void Input_mouse(int button, int state, float x, float y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			//start button
			if (-0.45f < x && x < 0.45f && -0.06f < y && y < 0.1f)
			{
				game_start = true;
				select_menu = 0;
			}

			//quit button
			if (0.013f < x && x < 0.45f && -0.73f < y && y < -0.57f)
				exit(0);
		}

	}

	void Input_motion(float x, float y)
	{
		//start button
		if (-0.45f < x && x < 0.45f && -0.06f < y && y < 0.1f)
		{
			select_menu = 1;
		}

		//quit button
		else if (0.013f < x && x < 0.45f && -0.73f < y && y < -0.57f)
		{
			select_menu = -1;
		}

		else
		{
			select_menu = 0;
		}
	}

};


#endif