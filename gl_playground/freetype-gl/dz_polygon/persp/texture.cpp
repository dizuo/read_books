#include "texture.h"

#include <stdio.h>
#include <stdlib.h>

#define logi printf

const char* getGLErrorInfo(int errorId)
{
	switch (errorId)
	{
	case GL_INVALID_ENUM:
		return ("GL Invalid Enum\n");
	case GL_INVALID_VALUE:
		return ("GL Invalid Value\n");
	case GL_INVALID_OPERATION:
		return ("GL Invalid Operation\n");
	case GL_OUT_OF_MEMORY:
		return ("GL Out Of Memory\n");
		//case GL_INVALID_FRAMEBUFFER_OPERATION:
		//	return ("GL Invalid FrameBuffer Operation\n");
		//case GL_TABLE_TOO_LARGE:
		//	return ("GL Table Too Large\n");
	};

	return "GL Undefined Error";
}
void checkGLError(const char* op)
{
	for (GLint error = glGetError(); error; error = glGetError())
	{
		printf("after %s() glError (0x%x), info = %s\n", op, error, getGLErrorInfo(error));
	}
}

void Texture::destroy()
{
#ifndef ES_ANDROID
	if (mId != 0)
	{
		glDeleteTextures(1, &mId);
		mId = 0;
	}
#endif
}

static const char* VERTEX_SHADER = "attribute vec4 a_position;\n"\
"attribute vec2 a_texcoord;\n"\
"varying vec2 v_texcoord;\n"\
"void main() {\n"\
"  gl_Position = a_position;\n"\
"  v_texcoord = a_texcoord;\n"\
"}\n";

static const char* FRAGMENT_SHADER = "precision mediump float;\n"\
"uniform sampler2D tex_sampler;\n"\
"varying vec2 v_texcoord;\n"\
"void main() {\n"\
"  gl_FragColor = texture2D(tex_sampler, v_texcoord);\n"\
"}\n";

void Texture::create_texture(int w, int h)
{
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);
	checkGLError("gen_texture");

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	checkGLError("create_texture");

	if (!glIsTexture(mId))
	{
		logi("bad texture object");
	} 	logi("create texture object [ %d, %d ]", w, h);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	mProgram = glCreateProgram();
	
	GLuint vert_shader = ftgl::shader_compile(VERTEX_SHADER, GL_VERTEX_SHADER);
	glAttachShader(mProgram, vert_shader);
	glDeleteShader(vert_shader);

	GLuint frag_shader = ftgl::shader_compile(FRAGMENT_SHADER, GL_FRAGMENT_SHADER);
	glAttachShader(mProgram, frag_shader);
	glDeleteShader(frag_shader);
	
	glLinkProgram(mProgram);

	GLint link_status;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &link_status);
	if (link_status == GL_FALSE)
	{
		GLchar messages[256];
		glGetProgramInfoLog(mProgram, sizeof(messages), 0, &messages[0]);
		fprintf(stderr, "%s\n", messages);
		exit(1);
	}

}

void Texture::copy_from_screen(int x, int y, int w, int h)
{
	// logi("copy texture object [ %d,%d,%d,%d ]\n", x, y, w, h);

	glBindTexture(GL_TEXTURE_2D, mId);
	checkGLError("beg_cp_texture");

#if 0
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, w, h, 0);
	checkGLError("cp_texture");			// 0x502 error.
#endif

	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, x, y, w, h);
	checkGLError("cp_sub_texture");		// 0x502 error.

}

void Texture::render_to_screen(int w, int h)
{
	// Bind default FBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, w, h);

#if CLEAR_SCREEN
	glClearColor(0.7, 0.7, 0.7, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
#endif

	// Use our shader program
	glUseProgram(mProgram);
	checkGLError("glUseProgram");

	glActiveTexture(GL_TEXTURE0);
	checkGLError("glActiveTexture");

	int u_sampler = glGetUniformLocation(mProgram, "tex_sampler");
	int a_tex = glGetAttribLocation(mProgram, "a_texcoord");
	int a_pos = glGetAttribLocation(mProgram, "a_position");

	glBindTexture(GL_TEXTURE_2D, mId);
	checkGLError("glBindTexture");
	glUniform1i(u_sampler, 0);
	checkGLError("glUniform1i");

	// full screen.
	// float vertices[] = { -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, -1.0 };
	// float center_quad[] = { -.5, .5, -.5, -.5, .5, .5, .5, -.5 };
	float lb_quad[] = { -1.0, .0, -1.0, -1.0, .0, .0, 0.0, -1.0 };

	const float texcoords[] = { 0, 1, 0, 0, 1, 1, 1, 0 };

	glVertexAttribPointer(a_pos,
		2, GL_FLOAT, GL_FALSE, 0, lb_quad);
	glVertexAttribPointer(a_tex,
		2, GL_FLOAT, GL_FALSE, 0, texcoords);

	glEnableVertexAttribArray(a_pos);
	glEnableVertexAttribArray(a_tex);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableVertexAttribArray(a_tex);
	glDisableVertexAttribArray(a_pos);

	glUseProgram(0);
}