#ifdef USE_SOIL
#include "SOIL.h"
#endif

#include "tess_helper.h"

#include <stdio.h>
#include <limits>

#include <gl/glut.h>

void init();
void reshape(int width, int height);
void render();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);

int win_width = 600;

TessHelper g_helper;
int poly_mode = TessHelper::ADD_POLY;

// MI3 aspect : 1080 / 1920 = 0.56
// Nexus4 aspect : 768 / 1196 = 0.64
// #define MI3_ASPECT
int win_height = 800;

char bmp_name[256];

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("find_car");
	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	init();
	glutMainLoop();

	return 0;
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	g_helper.restore("./data/path.txt");
}

void reshape(int width, int height)
{
	win_width = width;
	win_height = height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

static int is_down = 0;

void mouse(int button, int state, int x, int y)
{
	int gl_ortho_y = win_height - y;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		is_down = 1;
		printf("%d,%d ", x, gl_ortho_y);

		g_helper.add_pnt(poly_mode, x, gl_ortho_y);
	}
	else
	{
		is_down = 0;
	}

	glutPostRedisplay();
}

void motion(int x, int y)
{
	const float TOUCH_SCALE_FACTOR = 180.0f / 320;

	if (is_down == 0)
	{
		return;
	}

	glutPostRedisplay();
}

void my_swap(unsigned char* p1, unsigned char* p2)
{
	unsigned char tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void save_capture(const char* fname)
{
	static bool has_capture = false;
	if (has_capture)
	{
		return;
	}

	has_capture = true;
	typedef unsigned char uchar;

	uchar* buf = new uchar[win_width * win_height * 4];

	uchar* tmp = new uchar[win_width * win_height * 4];
	uchar* pdst = tmp;

	glReadPixels(0, 0, win_width, win_height, GL_RGBA, GL_UNSIGNED_BYTE, buf);

	for (int y1 = win_height - 1, y2 = 0; y2 < y1; y1--, y2++)
		for (int x = 0; x < win_width; x++)
			for (int t = 0; t < 4; t++)
				my_swap(buf + (y1*win_width + x) * 4 + t, buf + (y2*win_width + x) * 4 + t);

#ifdef USE_SOIL
	SOIL_save_image(fname, SOIL_SAVE_TYPE_BMP, win_width, win_height, 4, buf);
#endif

	delete[] buf;
}

void render()
{
	glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// g_helper.test_render();
	g_helper.render();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(1);
	}

	const float step = 5.0f;

	switch (key)
	{
	case 'b':
		g_helper.backspace(poly_mode);
		break;

	case '0':
		poly_mode = TessHelper::ADD_POLY;
		break;
	case '1':
		poly_mode = TessHelper::ADD_HOLE;
		break;

	case 'l':
	case 'L':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'f':
	case 'F':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case ' ':
		g_helper.clear();
		break;

	default:
		break;
	}

	glutPostRedisplay();
}
