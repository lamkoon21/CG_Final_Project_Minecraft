#include "ui.h"


void UI::Init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void UI::Render(int screenWidth, int screenHeight)
{
	int midX = screenWidth / 2;
	int midY = screenHeight / 2;

	glScissor(midX - 1, midY - 13, 2, 26);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glScissor(midX - 13, midY - 1, 26, 2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDisable(GL_SCISSOR_TEST);

	int bh = screenHeight / 14;
	glScissor(midX - 4.5f * bh, 0, bh * 9, bh);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float screen_ratio = static_cast<float>(screenWidth) / screenHeight;

	float ftop = 2.0f / 14.0f;
	float fright = 4.5f * ftop / screen_ratio;
	float itv = 0.005f / screen_ratio;

	float vertices[] = {
		 fright - itv,  -1.0f + ftop, 0.0f, 1.0f, 1.0f,
		-fright - itv,  -1.0f + ftop, 0.0f, 0.0f, 1.0f,
		 fright - itv, -1.0f, 0.0f, 1.0f, 0.0f,
		 fright - itv, -1.0f, 0.0f, 1.0f, 0.0f,
		-fright - itv,  -1.0f + ftop, 0.0f, 0.0f, 1.0f,
		-fright - itv, -1.0f, 0.0f, 0.0f, 0.0f
	};

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // bind to buffer
    glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), vertices, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void UI::Render2(int screenWidth, int screenHeight, int n)
{
	float screen_ratio = static_cast<float>(screenWidth) / screenHeight;
	float itv = 0.005f / screen_ratio;
	
	int bh = screenHeight / 14;
	float ftop = 2.0f / 14.0f;
	float fleft = -4.5f * ftop / screen_ratio;
	float fright = -fleft / 4.5f;
	
	fleft += fright * n;

	float vertices[] = {
		fleft + fright - itv, -1.0f + ftop, -0.1f, 1.0f, 1.0f,
		fleft - itv,			-1.0f + ftop, -0.1f, 0.0f, 1.0f,
		fleft + fright - itv, -1.0f,		  -0.1f, 1.0f, 0.0f,
		fleft + fright - itv, -1.0f,		  -0.1f, 1.0f, 0.0f,
		fleft - itv,			-1.0f + ftop, -0.1f, 0.0f, 1.0f,
		fleft - itv,			-1.0f,		  -0.1f, 0.0f, 0.0f
	};
	
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// bind to buffer
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), vertices, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}