#ifndef UI_H
#define UI_H


#include "glm/glm.hpp"
#include "../shader/shader.h"

class UI
{
private:
	unsigned int VAO, VBO;
public:
	void Init();
	void Render(int screenWidth, int screenHeight);
	void Render2(int screenWidth, int screenHeight, int n);
};



#endif