#include<GL/glut.h>
#include<cmath>

const double pi = 3.141592654;
const int width = 340, height = 640;
GLdouble A, B, C, D;

void init() {
	glClearColor(1, 1, 1, 0);
	glColor3f(0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-width, width, -height, height);

	A = width / 4.0;
	B = 0.0;
	C = D = height / 2.0;
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-width, -C);
    glVertex2f(width, -C);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0, -C);
    glVertex2f(0, C);
    glEnd();
	glBegin(GL_LINE_STRIP);
	for (GLdouble x = -4.0; x < 4.0; x += 0.005) {
		GLdouble f = sin(pi * x) / (pi * x);
		glVertex2d(A * x + B, C * f - D);
	}
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(width, height* 0.5);
	glutCreateWindow("Session 1 2018-2019 exercise2");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();

    return 0;
}