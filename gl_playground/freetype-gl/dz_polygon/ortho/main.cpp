#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <math.h>

#include "polyon_2d.h"

#include "soil/SOIL.h"
#include <GLFW3/glfw3.h>

// ------------------------------------------------------- global variables ---

unsigned int g_texid = 0;
Polygon2D* g_poly = NULL;

// ------------------------------------------------------- global variables ---

// ----------------------------------------------------------------------------

void my_upload(const char* fname)
{
	unsigned char* buffer = NULL;
	int width = 0;
	int height = 0;
	int channel = 0;
	buffer = SOIL_load_image(fname, &width, &height, &channel, 4);
	if (!buffer)
		return;

	if (!g_texid)
	{
		glGenTextures(1, &g_texid);
	}

	glBindTexture(GL_TEXTURE_2D, g_texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
#if 0
	int ch_w = width, ch_h = height;
	unsigned char* data = new unsigned char[ch_w * ch_h * channel];
	for (int y = 0; y < ch_h; y++)
	{
		for (int x = 0; x < ch_w; x++)
		{
			unsigned char* psrc = buffer + (y * width + x) * channel;
			unsigned char* pdst = buffer + (y * ch_w + x) * channel;
			memcpy(pdst, psrc, channel);
		}
	}
	SOIL_save_image("child.bmp", SOIL_SAVE_TYPE_BMP, ch_w, ch_h, channel, data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ch_w, ch_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
#endif

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	free(buffer);
	
}

// ---------------------------------------------------------------- display ---
void display(GLFWwindow* window)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	GLint width = viewport[2];
	GLint height = viewport[3];

	g_poly->render();

	glfwSwapBuffers(window);
}


// ---------------------------------------------------------------- reshape ---
void reshape(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	if (!g_poly)
		g_poly = new Polygon2D();

	g_poly->reshape(width, height);
}

// --------------------------------------------------------------- keyboard ---
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		delete g_poly;

		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == ' ')
	{
		g_poly->clear();
	}
}

bool has_mouse_down = false;
void mouse(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
	{
		has_mouse_down = true;
		printf("down\n");
	}
	else if (action == GLFW_RELEASE)
	{
		has_mouse_down = false;
		printf("release\n");
	}

}

void cursor_position_callback(GLFWwindow* window, double x, double y)
{
	if (has_mouse_down)
	{
		int width = 0;
		int height = 0;
		glfwGetWindowSize(window, &width, &height);

		vec2 pen = { { x, height - y } };

		printf("%f, %f\n", x, height - y);
		has_mouse_down = false;	// only once.

		g_poly->add_point(x, height - y);

	}
}

/* -------------------------------------------------------- error-callback - */
void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

// ------------------------------------------------------------------- main ---

int main(int argc, char **argv)
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(1, 1, "PolygonPatternFill", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(window, reshape);
	glfwSetWindowRefreshCallback(window, display);
	glfwSetKeyCallback(window, keyboard);
	glfwSetMouseButtonCallback(window, mouse);
	glfwSetCursorPosCallback(window, cursor_position_callback);

#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif
	
	my_upload("./data/flower@2x.png");
	vec2 tex_pat = { {48, 48 } };

	glfwSetWindowSize(window, 800, 600);
	glfwShowWindow(window);

	glBindTexture(GL_TEXTURE_2D, g_texid);

	g_poly->set_texture_pattern(tex_pat);
	Polygon2D::fufill_test_data(*g_poly);

	while (!glfwWindowShouldClose(window))
	{
		display(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
