#include <stdlib.h>
#include <glut.h>
#include <fstream>

FILE *externalFile;
float pos[2][2];
using namespace std;
// Set Window Size
GLsizei windowWidth = 800, windowHeight = 640;
void initialize(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void plotPoint(GLint x, GLint y) {
	glLineWidth(2.5); // For Line
	glBegin(GL_LINES);
	//glBegin(GL_POINTS);
	glVertex2d(x, y);
	//glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(15, 0, 0);
	glEnd();
}

// Centering pressing to the plot points (Calculate from the origin [bottom left])
void mousePlotPoint(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		plotPoint(xMouse, windowHeight - yMouse);
	glFlush();
}

// Display function
void displayFunc(void)
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (int colum = 0; colum < 2; colum++)
	{
		glVertex2f(pos[colum][0], pos[colum][1]);
	}
	glEnd();
	glutMouseFunc(mousePlotPoint);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

// Reshape Function
void reshapeFunc(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
	windowWidth = newWidth; // Location of mouse pressing on width
	windowHeight = newHeight; // Location of mouse pressing on height
}

// Read external file function
void readExfile(const char *filename)
{
	int row = 0;
	int col = 0;

	ifstream into(filename); // input

	int numOfColumns = 2;
	int numOfRows = 2;

	for (row = 0; row < numOfRows; row++)
	{
		for (col = 0; col < numOfColumns; col++)
		{
			into >> pos[row][col];
		}
	}
}

// Main Function
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Tutorial 1 (Points)");

	initialize();
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(reshapeFunc);
	glutMainLoop();
	glutMouseFunc(mousePlotPoint);
	readExfile("externalfile.txt");
}
