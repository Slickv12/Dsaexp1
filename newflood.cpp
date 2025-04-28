#include <GL/glut.h>
#include <cmath>

struct Point { GLint x, y; };
struct Color { GLfloat r, g, b; };

void init() {
	glClearColor(1, 1, 1, 0);
	glColor3f(0, 0, 0);
	glPointSize(1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

Color getPixelColor(GLint x, GLint y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, const Color& color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void floodFill(GLint x, GLint y, const Color& oldColor, const Color& newColor) {
	Color current = getPixelColor(x, y);
	if (current.r == oldColor.r && current.g == oldColor.g && current.b == oldColor.b) {
		setPixelColor(x, y, newColor);
		floodFill(x+1, y, oldColor, newColor);
		floodFill(x-1, y, oldColor, newColor);
		floodFill(x, y+1, oldColor, newColor);
		floodFill(x, y-1, oldColor, newColor);
		floodFill(x+1, y+1, oldColor, newColor);
		floodFill(x-1, y-1, oldColor, newColor);
		floodFill(x-1, y+1, oldColor, newColor);
		floodFill(x+1, y-1, oldColor, newColor);
	}
}

void onMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Color oldColor = {1, 1, 1}; // white
		Color newColor = {1, 0, 0}; // red
		floodFill(150, 150, oldColor, newColor);
	}
}

void display()
{ glColor3f(0,1,0); 
	glBegin(GL_LINE_LOOP);
	glVertex2i(100,100);
	glVertex2i(200,100);
	glVertex2i(200,200);
	glVertex2i(100,200);
	glEnd();
	glFlush();

} 



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("OpenGL DDA & Flood Fill");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}
