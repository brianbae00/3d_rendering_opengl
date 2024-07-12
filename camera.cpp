#include "Camera.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

Camera::Camera()
    : distance(30.0f), angleX(0.0f), angleY(0.0f), x(30.f), y(348.0f), z(-893.0f), view_vector(glm::fvec3(0)), mode(false) {}

void Camera::updatePosition(float dx, float dy, int type)
{
    if (type == 0)
    {
        mode = false;
        //==================method1
        //glm::fvec3 center = glm::fvec3(ox, oy, oz);
        //glm::fvec3 position = glm::fvec3(x, y, z);
        //glm::fvec3 view = position - center;
        //float size = glm::length(view);
        //glm::fvec3 forward = glm::normalize(glm::fvec3(ox - x, oy - y, oz - z));
        //glm::fvec3 right = glm::normalize(glm::cross(forward, up_vector));
        //glm::fvec3 up = glm::cross(right, forward);
        //dx *= 0.3f;
        //dy *= 0.3f;
        //x += right.x * dx + up.x * dy;
        //y += right.y * dx + up.y * dy;
        //z += right.z * dx + up.z * dy;
        //glm::fvec3 vec = size * glm::normalize(glm::fvec3(x - ox, y - oy, z - oz));
        //x = ox + vec.x;
        //y = oy + vec.y;
        //z = oz + vec.z;

        //========================method2
        //dx *= 0.001f;
        //dy *= 0.001f;
        //glm::fvec3 center = glm::fvec3(ox, oy, oz);
        //glm::fvec3 position = glm::fvec3(x, y, z);
        //glm::fvec3 view = position - center;
        //float size = glm::length(view);
        //glm::fvec3 forward = glm::normalize(glm::fvec3(ox - x, oy - y, oz - z));
        //glm::fvec3 right = glm::normalize(glm::cross(forward, up_vector));
        //glm::fvec3 up = glm::cross(right, forward);
        //glm::quat quaternion1 = glm::angleAxis(dx,glm::fvec3(0,1,0));
        ////glm::quat quaternion1 = glm::angleAxis(dx,up);
        ////glm::quat quaternion2 = glm::angleAxis(dy, right);
        //glm::quat quaternion2 = glm::angleAxis(dy, glm::fvec3(1,0,0));
        //glm::fvec3 new_view = size * glm::normalize(quaternion2 * quaternion1 * view);
        //x = ox + new_view.x;
        //y = oy + new_view.y;
        //z = oz + new_view.z;
        
        //=================method3
        dx *= -0.001f;
        dy *= 0.001f;

        glm::fvec3 center = glm::fvec3(ox, oy, oz);
        glm::fvec3 position = glm::fvec3(x, y, z);
        glm::fvec3 view = position - center;
        float size = glm::length(view);

        glm::fvec3 forward = glm::normalize(view);
        glm::fvec3 right = glm::normalize(glm::cross(up_vector, forward));
        glm::fvec3 up = glm::cross(forward, right);

        glm::quat pitch = glm::angleAxis(dy, right);
        glm::quat yaw = glm::angleAxis(dx, up_vector); 

        glm::quat combined_rotation = yaw * pitch;
        glm::fvec3 new_view = glm::normalize(glm::rotate(combined_rotation, view)) * size;

        x = ox + new_view.x;
        y = oy + new_view.y;
        z = oz + new_view.z;

        forward = glm::normalize(center - glm::fvec3(x, y, z));
        right = glm::normalize(glm::cross(up_vector, forward));
        up_vector = glm::cross(forward, right);

    }
    else if (type == 1)
    {
        mode = true;
        view_vector = glm::fvec3(x - ox, y - oy, z - oz);
        if (std::abs(dx) > std::abs(dy)) return;
        if (dy > 0) // zoom out
        {
            view_vector += glm::normalize(view_vector) * 15.f;
        }
        else if (dy < 0) // zoom in
        {
            view_vector -= glm::normalize(view_vector) * 15.f;
        }
    }
}

void Camera::apply()
{
    if (!mode)
    {
        // 이동 모드
        gluLookAt(x, y, z, ox, oy, oz, up_vector.x, up_vector.y, up_vector.z);
    }
    else
    {
        // 줌 모드
        x = ox + view_vector.x;
        y = oy + view_vector.y;
        z = oz + view_vector.z;
        gluLookAt(x, y, z, ox, oy, oz, up_vector.x, up_vector.y, up_vector.z);
    }
}
