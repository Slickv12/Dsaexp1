#include <GL/glut.h>
#include <cmath>

struct Point {
    float x, y;
};

// Koch Curve Drawing Function
void drawKochCurve(Point p1, Point p2, int depth) {
    if (depth == 0) {
        glBegin(GL_LINES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glEnd();
        return;
    }

    Point a, b, peak;

    // Divide line into thirds
    a.x = (2 * p1.x + p2.x) / 3;
    a.y = (2 * p1.y + p2.y) / 3;

    b.x = (p1.x + 2 * p2.x) / 3;
    b.y = (p1.y + 2 * p2.y) / 3;

    // Find the peak of the equilateral triangle
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float length = sqrt(dx * dx + dy * dy);
    float angle = atan2(dy, dx) - M_PI / 3;

    peak = { (float)(a.x + cos(angle) * length), (float)(a.y + sin(angle) * length) };

    drawKochCurve(p1, a, depth - 1);
    drawKochCurve(a, peak, depth - 1);
    drawKochCurve(peak, b, depth - 1);
    drawKochCurve(b, p2, depth - 1);
}

// Display Callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 1);

    Point p1 = { -0.8f, 0.0f };
    Point p2 = { 0.8f, 0.0f };

    int depth = 3; // You can change this to increase or decrease the level of recursion
    drawKochCurve(p1, p2, depth);

    glFlush();
}

// Setup OpenGL
void init() {
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(-1, 1, -1, 1);
}

// Main Function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Koch Curve");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

