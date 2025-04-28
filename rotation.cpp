#include <GL/glut.h>
#include <math.h>

double parr[8];

void init() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    glColor3f(1, 0, 1);
    gluOrtho2D(-500, 500, -500, 500); // Left, right, bottom, top
    
    // Polygon Default
    parr[0] = 100;  // x
    parr[1] = 100;  // y

    parr[2] = 300;
    parr[3] = 100;

    parr[4] = 300;
    parr[5] = 300;

    parr[6] = 100;
    parr[7] = 300;
}

double degreeToRad(double deg) {
    return 3.14 * (deg / 180);
}

void polygon() {
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(parr[0], parr[1]);
    glVertex2f(parr[2], parr[3]);

    glVertex2f(parr[4], parr[5]);
    glVertex2f(parr[6], parr[7]);
    glEnd();

    glFlush();
}

void drawCorodinates() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);
    glPointSize(4);

    glBegin(GL_LINES);
    glVertex2f(-500, 0);
    glVertex2f(500, 0);

    glVertex2f(0, 500);
    glVertex2f(0, -500);
    glEnd();

    glColor3f(1, 0, 0);

    glBegin(GL_POINTS);
    glVertex2f(0, 0);
    glEnd();

    glFlush();
}

// Translation
void translate2d() {
    int i = 0;
    int tx = 200, ty = 50;

    for (i = 0; i <= 7; i = i + 2) {
        parr[i] = parr[i] + tx;
    }

    for (i = 1; i <= 7; i = i + 2) {
        parr[i] = parr[i] + ty;
    }

    polygon();
}

// Rotation
void rotation() {
    double angle = 180, rad, x, y;
    rad = degreeToRad(angle);

    for (int i = 0; i < 8; i = i + 2) {
        x = parr[i] * cos(rad) - parr[i + 1] * sin(rad);
        y = parr[i] * sin(rad) + parr[i + 1] * cos(rad);

        parr[i] = x;
        parr[i + 1] = y;
    }

    polygon();
}

// Scaling
void scaling2d() {
    // 2 units in x 
    // 2 units in y
    int i = 0;
    double x = 1.5, y = 1.5;

    for (i = 0; i < 7; i = i + 2) {
        parr[i] = parr[i] * x;
        parr[i + 1] = parr[i + 1] * y;
    }

    polygon();
}

// Reflection
void reflectX() {
    // Reflection matrix across the X-axis:
    // | 1   0   0 |
    // | 0  -1   0 |
    // | 0   0   1 |

    glScalef(1.0f, -1.0f, 1.0f);  // Reflect across the x-axis

    polygon();
}
void reflectY() {
    // Reflection matrix across the Y-axis:
    // | -1  0   0 |
    // |  0  1   0 |
    // |  0  0   1 |

    glScalef(-1.0f, 1.0f, 1.0f);

    polygon();
}

// Rotation About an Arbitrary Point
void rotationArbitraryPoint() {
    double angle = 45.0, rad, x, y;
    rad = degreeToRad(angle);

    double px = 100, py = 100; // The arbitrary point around which to rotate

    // Translate the polygon so that the arbitrary point becomes the origin
    for (int i = 0; i < 8; i = i + 2) {
        parr[i] = parr[i] - px;
        parr[i + 1] = parr[i + 1] - py;
    }

    // Rotate around the origin (0, 0)
    for (int i = 0; i < 8; i = i + 2) {
        x = parr[i] * cos(rad) - parr[i + 1] * sin(rad);
        y = parr[i] * sin(rad) + parr[i + 1] * cos(rad);

        parr[i] = x;
        parr[i + 1] = y;
    }

    // Translate back to the original position
    for (int i = 0; i < 8; i = i + 2) {
        parr[i] = parr[i] + px;
        parr[i + 1] = parr[i + 1] + py;
    }

    polygon();
}

void menu(int ch) {
    drawCorodinates();
    switch (ch) {
    case 1:
        polygon();
        break;

    case 2:
        translate2d();
        break;
    case 3:
        scaling2d();
        break;
    case 4:
        rotation();
        break;
 
    case 7:
        rotationArbitraryPoint(); // Added rotation around arbitrary point
        break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("2D Transformation");
    init();
    glutDisplayFunc(drawCorodinates);

    glutCreateMenu(menu);
    glutAddMenuEntry("1 Display Polygon", 1);
    glutAddMenuEntry("2 Translate", 2);
    glutAddMenuEntry("3 Scaling", 3);
    glutAddMenuEntry("4 Rotation", 4);
    
    glutAddMenuEntry("5 Rotation About Arbitrary Point", 7); // Added menu entry for the new rotation
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}

