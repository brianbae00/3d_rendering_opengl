#include "STLObject.h"
#include "Camera.h"
#include "MouseHandler.h"
#include "Lighting.h"
#include "Circle.h"
#include <GL/glut.h>
#include <iostream>

Camera camera;
MouseHandler mouseHandler;
CircleManager circleManager;
STLObject object1;
STLObject object2;
STLObject object3;
STLObject object4;

Lighting lighting;
std::vector<std::vector<float>> normals;
std::vector<std::vector<float>> normals2;
std::vector<std::vector<float>> normals3;
std::vector<std::vector<float>> normals4;
std::vector<std::vector<std::vector<float>>> vertices;
std::vector<std::vector<std::vector<float>>> vertices2;
std::vector<std::vector<std::vector<float>>> vertices3;
std::vector<std::vector<std::vector<float>>> vertices4;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera.apply();

    glTranslatef(mouseHandler.objectPosX, mouseHandler.objectPosY, 0.0);
    glRotatef(mouseHandler.objectAngleX, 1.0, 0.0, 0.0);
    glRotatef(mouseHandler.objectAngleY, 0.0, 1.0, 0.0);

    object1.renderByASCII(normals, vertices, 1.f, 0.0f, 0.0f);
    object2.renderByASCII(normals2, vertices2, 0.0f, 1.f, 0.0f);
    object3.renderByASCII(normals3, vertices3, 0.0f, 0.0f, 1.f);
    object4.renderByASCII(normals4, vertices4, 1.0f, 1.0f, 0.f);

    circleManager.drawCircles();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(w) / static_cast<double>(h), 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
    std::vector<int> circle_num;
    if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON) 
    {
        int window_height = glutGet(GLUT_WINDOW_HEIGHT);
        float gl_x = static_cast<float>(x);
        float gl_y = static_cast<float>(window_height - y); // Invert y coordinate

        if (circleManager.checkClick(gl_x, gl_y , circle_num) && state==GLUT_DOWN) 
        {
            switch (circle_num[0])
            {
            case 1:
                object1.setVisible(!object1.getVisible());
                break;
            case 2:
                object2.setVisible(!object2.getVisible());
                break;
            case 3:
                object3.setVisible(!object3.getVisible());
                break;
            case 4:
                object4.setVisible(!object4.getVisible());
                break;
            default:
                break;
            }
        }
        else 
        {
            mouseHandler.handleButton(button, state, x, y);
        }
    }
}

void motion(int x, int y)
{
    mouseHandler.handleMotion(x, y, camera, object1);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        exit(0);
    }
    else if (key == '1')
    {
        object1.setVisible(!object1.getVisible());
        display();
    }
    else if (key == '2')
    {
        object2.setVisible(!object2.getVisible());
        display();
    }
    else if (key == '3')
    {
        object3.setVisible(!object3.getVisible());
        display();
    }
    else if (key == '4')
    {
        object4.setVisible(!object4.getVisible());
        display();
    }
}

void initOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    lighting.setup();
}

void initCircles() {
    circleManager.addCircle(100.0f, 1000.0f, 25.0f, 1.0f, 0.0f, 0.0f); // Red
    circleManager.addCircle(100.0f, 900.0f, 25.0f, 0.0f, 1.0f, 0.0f); // Green
    circleManager.addCircle(100.0f, 800.0f, 25.0f, 0.0f, 0.0f, 1.0f); // Blue
    circleManager.addCircle(100.0f, 700.0f, 25.0f, 1.0f, 1.0f, 0.0f); // Yellow
}

int main(int argc, char** argv)
{
    object1.readASCIISTL("./eye00001.stl", normals, vertices);
    object2.readASCIISTL("./eye00002.stl", normals2, vertices2);
    object3.readASCIISTL("./eye00003.stl", normals3, vertices3);
    object4.readASCIISTL("./eye00004.stl", normals4, vertices4);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("STL Viewer");

    initOpenGL();
    initCircles();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
