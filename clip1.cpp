#include <stdio.h>
#include <GL/glut.h>

typedef struct // Structure to hold coordinates of a point
{
    float x;
    float y;
} PT;

// Global variables
int n, i, j;
PT p1, p2, p[20], pp[20];

// Left Clipping
void left() {
    j = 0;
    for (i = 0; i < n; i++) {
        if (p[i].x < p1.x && p[i + 1].x >= p1.x) { // Case 1: Outside to Inside
            pp[j].y = p[i].y + (p[i + 1].y - p[i].y) * (p1.x - p[i].x) / (p[i + 1].x - p[i].x);
            pp[j].x = p1.x;
            j++;
            pp[j] = p[i + 1]; // Save inside point
            j++;
        } else if (p[i].x >= p1.x && p[i + 1].x >= p1.x) { // Case 2: Inside to Inside
            pp[j] = p[i + 1];
            j++;
        } else if (p[i].x >= p1.x && p[i + 1].x < p1.x) { // Case 3: Inside to Outside
            pp[j].y = p[i].y + (p[i + 1].y - p[i].y) * (p1.x - p[i].x) / (p[i + 1].x - p[i].x);
            pp[j].x = p1.x;
            j++;
        }
    }
    n = j;
    for (i = 0; i < n; i++) p[i] = pp[i];
    p[n] = p[0];
}

// Right Clipping
void right() {
    j = 0;
    for (i = 0; i < n; i++) {
        if (p[i].x > p2.x && p[i + 1].x <= p2.x) {
            pp[j].y = p[i].y + (p[i + 1].y - p[i].y) * (p2.x - p[i].x) / (p[i + 1].x - p[i].x);
            pp[j].x = p2.x;
            j++;
            pp[j] = p[i + 1];
            j++;
        } else if (p[i].x <= p2.x && p[i + 1].x <= p2.x) {
            pp[j] = p[i + 1];
            j++;
        } else if (p[i].x <= p2.x && p[i + 1].x > p2.x) {
            pp[j].y = p[i].y + (p[i + 1].y - p[i].y) * (p2.x - p[i].x) / (p[i + 1].x - p[i].x);
            pp[j].x = p2.x;
            j++;
        }
    }
    n = j;
    for (i = 0; i < n; i++) p[i] = pp[i];
    p[n] = p[0];
}

// Top Clipping (Fixed)
void top() {
    j = 0;
    for (i = 0; i < n; i++) {
        if (p[i].y > p2.y && p[i + 1].y <= p2.y) {  // Outside → Inside
            pp[j].x = p[i].x + (p[i + 1].x - p[i].x) * (p2.y - p[i].y) / (p[i + 1].y - p[i].y);
            pp[j].y = p2.y;
            j++;
            pp[j] = p[i + 1];
            j++;
        } else if (p[i].y <= p2.y && p[i + 1].y <= p2.y) {  // Inside → Inside
            pp[j] = p[i + 1];
            j++;
        } else if (p[i].y <= p2.y && p[i + 1].y > p2.y) {   // Inside → Outside
            pp[j].x = p[i].x + (p[i + 1].x - p[i].x) * (p2.y - p[i].y) / (p[i + 1].y - p[i].y);
            pp[j].y = p2.y;
            j++;
        }
    }
    n = j;
    for (i = 0; i < n; i++) p[i] = pp[i];
    p[n] = p[0];
}

// Bottom Clipping
void bottom() {
    j = 0;
    for (i = 0; i < n; i++) {
        if (p[i].y < p1.y && p[i + 1].y >= p1.y) {
            pp[j].x = p[i].x + (p[i + 1].x - p[i].x) * (p1.y - p[i].y) / (p[i + 1].y - p[i].y);
            pp[j].y = p1.y;
            j++;
            pp[j] = p[i + 1];
            j++;
        } else if (p[i].y >= p1.y && p[i + 1].y >= p1.y) {
            pp[j] = p[i + 1];
            j++;
        } else if (p[i].y >= p1.y && p[i + 1].y < p1.y) {
            pp[j].x = p[i].x + (p[i + 1].x - p[i].x) * (p1.y - p[i].y) / (p[i + 1].y - p[i].y);
            pp[j].y = p1.y;
            j++;
        }
    }
    n = j;
    for (i = 0; i < n; i++) p[i] = pp[i];
    p[n] = p[0];
}

// Draw the Polygon
void drawPolygon() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < n; i++) {
        glVertex2d(p[i].x, p[i].y);
    }
    glEnd();
}

// Mouse Function
void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINE_LOOP);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p1.x, p2.y);
        glEnd();
        left();
        right();
        top();
        bottom();
        drawPolygon();
    }
    glFlush();
}

// Display Function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p1.x, p2.y);
    glEnd();
    drawPolygon();
    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 500, 0, 500);
}

// Main Function
int main(int argc, char **argv) {
    printf("Enter Clipping Window (P1.x P1.y P2.x P2.y): ");
    scanf("%f %f %f %f", &p1.x, &p1.y, &p2.x, &p2.y);
    printf("Enter Number of Vertices: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter Vertex %d (x y): ", i + 1);
        scanf("%f %f", &p[i].x, &p[i].y);
    }
    p[n] = p[0];

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Sutherland Hodgman Polygon Clipping");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}

