//@author : peteryfren
// MACRO Define: 
// GLEW_STATIC
// FREEGLUT_STATIC

#include "GL/glew.h"
#include <gl/freeglut.h>

#include <iostream>
#include <string>
using namespace std;

void glew_init_test();

int main()
{
	int argc = 1;
	char* argv = "CWCApp";

	glutInit(&argc, &argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//--------------------------------------------

	int window = glutCreateWindow("OpenGL Output");

	glew_init_test();

	glutMainLoop();

	getchar();
	printf("any key pressed to exit...\n");

	return 0;
}

void glew_init_test()
{
	glewInit();
	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		cout << "Error:" << glewGetErrorString(err) << endl;
		return;
	}

	cout << "OpenGL Vendor: " << (char*)glGetString(GL_VENDOR) << "\n";
	cout << "OpenGL Renderer: " << (char*)glGetString(GL_RENDERER) << "\n";
	cout << "OpenGL Version: " << (char*)glGetString(GL_VERSION) << "\n\n";
	//cout << "OpenGL Extensions:\n" << (char*) glGetString(GL_EXTENSIONS) << "\n\n";

	// dump GL function pointer.
	printf("%x\n", glUseProgram);

}