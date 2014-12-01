#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gl/glut.h>

#include "overlap_eliminate_test.h"

#define CACHE_DAT ("path.dat")
#define SVG_DAT ("path.svg")

struct WindowCtrl
{
	enum { MAX_SIZE = 100 };
	int width;
	int height;
	char title[MAX_SIZE];
} g_window_ctrl;

OverlayEliminateTest g_ol_elim_app;

void render();
void init();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
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

	glutMouseFunc(mouse);
	glutMotionFunc(motion);
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

	g_ol_elim_app.set_tolerance(30);

	g_ol_elim_app.load_from_file(CACHE_DAT);
	g_ol_elim_app.eliminate();

}

void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if 0
	glColor4f(1, 0, 0, 1);
	glRecti(0, 0, 200, 200);

	int delta = 50;
	glColor4f(0.5, 0.5, 1.0f, 0.5f);
	glRecti(delta, delta, g_window_ctrl.width - delta, g_window_ctrl.height - delta);
#endif
	
	g_ol_elim_app.render();

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

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			OverlayEliminateTest::path_t* cur_path = g_ol_elim_app.get_cur_path();
			if (!cur_path)
			{
				OverlayEliminateTest::path_t path;
				path.push_back(Point(x, g_window_ctrl.height - y));
				g_ol_elim_app.add_path(path);
			}
			else
			{
				cur_path->push_back(Point(x, g_window_ctrl.height - y));
			}
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		g_ol_elim_app.reset_cur_path();
		g_ol_elim_app.eliminate();
		g_ol_elim_app.save_to_file(CACHE_DAT, false);
	}

	glutPostRedisplay();
}

void motion(int x, int y)
{}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		g_ol_elim_app.save_to_file(CACHE_DAT);
		g_ol_elim_app.save_to_svg(SVG_DAT);

		exit(1);
		break;
	case 'c':
		g_ol_elim_app.clear();
		g_ol_elim_app.reset_cur_path();
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

