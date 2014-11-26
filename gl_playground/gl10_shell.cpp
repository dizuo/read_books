//@author : peteryfren
//@date : 20141126

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gl/glut.h>

struct WindowCtrl
{
	enum { MAX_SIZE = 100 };
	int width;
	int height;
	char title[MAX_SIZE];
} g_window_ctrl;

void render();
void init();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char *argv[])
{
	g_window_ctrl.width = 500;
	g_window_ctrl.height = 500;
	strcpy(g_window_ctrl.title, "overlap_eliminate_demo");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(g_window_ctrl.width, g_window_ctrl.height);
	glutCreateWindow(g_window_ctrl.title);
	glutInitWindowPosition(0, 0);
	
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	
	init();
	
	glutMainLoop();

	getchar();
	return 0;
}

void init()
{
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor4f(1, 0, 0, 1);
	glRecti(0, 0, 200, 200);

	int delta = 50;
	glColor4f(0.5, 0.5, 1.0f, 0.5f);
	glRecti(delta, delta, g_window_ctrl.width - delta, g_window_ctrl.height - delta);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	g_window_ctrl.width = w;
	g_window_ctrl.height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, (GLfloat)w, 0.0f, (GLfloat)h, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(1);
		break;

	default:
		break;
	}
}