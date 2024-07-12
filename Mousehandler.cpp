#include "MouseHandler.h"
#include <iostream>

MouseHandler::MouseHandler()
    : leftButtonDown(false),
    rightButtonDown(false),
    objectSelected(false),
    prevX(0),
    prevY(0),
    objectPosX(0.0f),
    objectPosY(0.0f),
    objectAngleX(0.0f),
    objectAngleY(0.0f) {}

void MouseHandler::handleButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) 
    {
        leftButtonDown = (state == GLUT_DOWN);
        if (leftButtonDown) objectSelected = isObjectSelected(x, y);
    }
    else if (button == GLUT_RIGHT_BUTTON) 
    {
        rightButtonDown = (state == GLUT_DOWN);
        if (rightButtonDown) objectSelected = isObjectSelected(x, y);
    }
    else if (button == 3 || button == 4)
    {
        std::cout << "wheel" << std::endl;
    }

    prevX = x;
    prevY = y;
}

void MouseHandler::handleMotion(int x, int y, Camera& camera, STLObject& object) {
    int dx = x - prevX;
    int dy = y - prevY;

    if (leftButtonDown && !objectSelected) {
        camera.updatePosition((float)dx, (float)dy , 0);
    }
    else if (rightButtonDown && !objectSelected) {
        camera.updatePosition((float)dx, (float)dy , 1);
    }
    else if (leftButtonDown && objectSelected) {
        objectPosX += dx * 0.01f;
        objectPosY -= dy * 0.01f;
    }
    else if (rightButtonDown && objectSelected) {
        objectAngleY += dx * 0.5f;
        objectAngleX += dy * 0.5f;
    }

    prevX = x;
    prevY = y;
}

bool MouseHandler::isObjectSelected(int x, int y) {
    return false; 
}
