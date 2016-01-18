#ifndef TEXTURE_201601181350_H
#define TEXTURE_201601181350_H

#include "shader.h"

class Texture
{
public:

	Texture() : mId(0), mProgram(0) {}
	~Texture() {}

	void create_texture(int w, int h);
	void copy_from_screen(int x, int y, int w, int h);
	void render_to_screen(int w, int h);

	void destroy();

	GLuint mProgram;
	GLuint mId;
};

const char* getGLErrorInfo(int errorId);
void checkGLError(const char* op);

#endif