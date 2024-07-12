#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
class Camera {
public:
    float distance;
    float angleX;
    float angleY;
    float x;
    float y;
    float z;
    float ox = 10.f;
    float oy = 218.f;
    float oz = -893.f;
    glm::fvec3 view_vector;
    glm::fvec3 up_vector = glm::fvec3(0.0f, 1.0f, 0.0f);
    bool mode;

    Camera();
    void updatePosition(float dx, float dy, int type); // 0 : rotate , 1 : zoom 
    void apply();
};

#endif // CAMERA_H
