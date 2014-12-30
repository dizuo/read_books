/*  bezcurve.c
*  This program uses evaluators to draw a Bezier curve.
*/
#include <GL/glut.h>
#include <stdlib.h>

// 0 IN; // 1 OUT; // 2 OUT; // 3 IN
GLfloat ctrlpoints[4][3] = { { 234.0, 357.0, 0.0 },	{ 2.0, 490.0, 0.0 }, { 101.0, 65.0, 0.0 }, { 234.0, 186.0, 0.0 } };

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);	
	glEnable(GL_MAP1_VERTEX_3);
}

void renderBezier(float(*ctrlPnts)[3])
{
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlPnts[0][0]);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 30; i++) { glEvalCoord1f((GLfloat)i / 30.0); }
	glEnd();
	
	glPointSize(5.0);	/* The following code displays the control points as dots. */
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
		for (int i = 0; i < 4; i++) { glVertex3fv(&ctrlPnts[i][0]); }
	glEnd();
}

void display(void)
{
	const float mirX = 237.0f;
	float mirCtrlPnts[4][3] = { 0 };
	for (int i = 0; i < 4; i++) { mirCtrlPnts[i][1] = ctrlpoints[i][1]; }
	for (int i = 0; i < 4; i++) { mirCtrlPnts[i][0] = 2 * mirX - ctrlpoints[i][0]; }

	glClear(GL_COLOR_BUFFER_BIT);	

	renderBezier(ctrlpoints);
	renderBezier(mirCtrlPnts);

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) { exit(0); }
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Heart");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}