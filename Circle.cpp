#include "circle.h"
#include <iostream>

void CircleManager::addCircle(float cx, float cy, float radius, float r, float g, float b) {
    circles.push_back({ cx, cy, radius, r, g, b });
}

void CircleManager::drawCircles() {
    // Switch to 2D projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1920, 0, 1080);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw circles from the list
    for (const auto& circle : circles) {
        glColor3f(circle.r, circle.g, circle.b);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 100; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / 100.0f;
            float x = circle.radius * cosf(theta);
            float y = circle.radius * sinf(theta);
            glVertex2f(x + circle.cx, y + circle.cy);
        }
        glEnd();
    }

    // Restore previous projection and modelview matrices
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

bool CircleManager::isPointInCircle(float px, float py, const Circle& circle) {
    float dx = px - circle.cx;
    float dy = py - circle.cy;
    return (dx * dx + dy * dy) <= (circle.radius * circle.radius);
}

bool CircleManager::checkClick(float px, float py , std::vector<int>& num_circle) {
    num_circle.clear();
    for (const auto& circle : circles) {
        if (isPointInCircle(px, py, circle)) {
            std::cout << "Clicked inside circle at (" << circle.cx << ", " << circle.cy << ")\n";

            if (circle.r == 1.0f && circle.g == 0.0f)
                num_circle.emplace_back(1);
            else if (circle.r == 0.0f && circle.g == 1.0f)
                num_circle.emplace_back(2);
            else if (circle.b == 1.0f)
                num_circle.emplace_back(3);
            else if (circle.r == 1.0f && circle.g == 1.0f)
                num_circle.emplace_back(4);
            return true;
        }
    }
    return false;
}
