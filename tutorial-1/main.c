#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

double double_rand()
{
    return (double)rand() / (double)RAND_MAX;
}

static double v1 = -0.5;
static bool plus = false;
static double v1_offset = 0.02;

static void change_size(int w, int h)
{
    if (h == 0) {
        h = 1;
    }

    float ratio = w * 1.0 / h;
    // fprintf(stdout, "ratio: %f, w: %d, h: %d\n", ratio, w, h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45, ratio, 1, 100);

    glMatrixMode(GL_MODELVIEW);
}

static void process_keys(unsigned char key, int x, int y)
{
    fprintf(stderr, "Key: %d\n", key);
}

static void process_special_keys(int key, int x, int y)
{
    fprintf(stderr, "Special Key: %d\n", key);
    switch (key) {
    case GLUT_KEY_UP:
        v1_offset = v1_offset + 0.05;
        break;
    case GLUT_KEY_DOWN:
        v1_offset = v1_offset - 0.05;
        if (v1_offset < 0.0) {
            v1_offset = 0.02;
        }
    default:
        break;
    }
}

static void dispfun()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.5f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    v1 = v1 - 0.01;
    if (plus == false) {
        v1 = v1 - v1_offset;
        if (v1 <= -1.0) {
            plus = true;
        }
    } else {
        v1 = v1 + v1_offset;
        if (v1 >= 1.0) {
            plus = false;
        }
    }

    glColor3f(1.0f, 1.0f, 10.f);
    glBegin(GL_QUADS);
        glVertex3f(-0.25f,  0.25f, 0);
        glVertex3f(-0.50f, -0.25f, 0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.5f, -0.25f, 0);
        glVertex3f(0.25f, 0.25f, 0);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(v1, v1,0.0);
        glVertex3f(0.5,0.0,0.0);
        glVertex3f(0.0,0.5,0.0);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glewExperimental = true;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Window's title");

    glutDisplayFunc(dispfun);
    // glutReshapeFunc(change_size);
    glutIdleFunc(dispfun);
    glutKeyboardFunc(process_keys);
    glutSpecialFunc(process_special_keys);

    fprintf(stderr, "OpenGL version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
    glutMainLoop();

    return 0;
}
