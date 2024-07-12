#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include "Camera.h"
#include "STLObject.h"

class MouseHandler {
public:
    bool leftButtonDown;
    bool rightButtonDown;
    bool objectSelected;
    int prevX;
    int prevY;
    float objectPosX;
    float objectPosY;
    float objectAngleX;
    float objectAngleY;

    MouseHandler();
    void handleButton(int button, int state, int x, int y);
    void handleMotion(int x, int y, Camera& camera, STLObject& object);

private:
    bool isObjectSelected(int x, int y);
};

#endif // MOUSEHANDLER_H
