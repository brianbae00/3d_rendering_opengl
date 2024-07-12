#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/glut.h>
#include <vector>

struct Circle {
    float cx, cy, radius;
    float r, g, b; // Color
};

class CircleManager {
public:
    void addCircle(float cx, float cy, float radius, float r, float g, float b);
    void drawCircles();
    bool isPointInCircle(float px, float py, const Circle& circle);
    bool checkClick(float px, float py, std::vector<int>& num_circle);

private:
    std::vector<Circle> circles;
};

#endif // CIRCLE_H
