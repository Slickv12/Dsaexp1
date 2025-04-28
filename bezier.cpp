#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

struct Point {
    float x, y;
};

vector<Point> controlPoints;

void drawControlPoints() {
    glPointSize(5);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    for (auto &pt : controlPoints) {
        glVertex2f(pt.x, pt.y);
    }
    glEnd();

    // Draw lines between control points
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINE_STRIP);
    for (auto &pt : controlPoints) {
        glVertex2f(pt.x, pt.y);
    }
    glEnd();
}

// Bezier equation
Point computeBezier(float t) {
    Point p;
    float u = 1 - t;

    // Using 4 control points (cubic Bezier)
    p.x = pow(u, 3) * controlPoints[0].x +
          3 * t * pow(u, 2) * controlPoints[1].x +
          3 * pow(t, 2) * u * controlPoints[2].x +
          pow(t, 3) * controlPoints[3].x;

    p.y = pow(u, 3) * controlPoints[0].y +
          3 * t * pow(u, 2) * controlPoints[1].y +
          3 * pow(t, 2) * u * controlPoints[2].y +
          pow(t, 3) * controlPoints[3].y;

    return p;
}

void drawBezierCurve() {
    if (controlPoints.size() == 4) {
        glColor3f(0, 1, 0);
        glBegin(GL_LINE_STRIP);
        for (float t = 0; t <= 1.0; t += 0.01) {
            Point p = computeBezier(t);
            glVertex2f(p.x, p.y);
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawControlPoints();
    drawBezierCurve();
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && controlPoints.size() < 4) {
        Point p;
        p.x = x;
        p.y = 500 - y;  // Invert y since OpenGL has origin at bottom-left
        controlPoints.push_back(p);
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        controlPoints.clear();
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(0, 500, 0, 500);  // 2D setup
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Bezier Curve - Select Control Points");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

