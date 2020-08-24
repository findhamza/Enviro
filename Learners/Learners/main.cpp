#include <windows.h>
#include <iostream>
#include <GL/glew.h>
#include <freeglut.h>

#pragma comment(lib,"glew32.lib")

GLuint ID;

void init() {
    glewInit();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
    glEnableClientState(GL_VERTEX_ARRAY);
    float data[][2] = { {50,50},{100,50},{10,100} };
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, (GLdouble)w, 0.0f, (GLdouble)h);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glVertexPointer(2, GL_FLOAT, 2 * sizeof(float), 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 300);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}