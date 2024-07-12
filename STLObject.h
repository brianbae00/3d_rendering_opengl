#ifndef STL_OBJECT_H
#define STL_OBJECT_H

#include <vector>
#include <string>
#include <GL/glut.h>

struct Vector3 {
    float x, y, z;
};

struct Triangle {
    Vector3 normal;
    Vector3 vertex1;
    Vector3 vertex2;
    Vector3 vertex3;
};

class STLObject
{
public:
    bool loadSTL(const std::string& filename);
    void renderObject(float r, float g, float b) const;
    void readASCIISTL(const std::string& filename, std::vector<std::vector<float>>& normals, std::vector<std::vector<std::vector<float>>>& vertices);
    void renderByASCII(std::vector<std::vector<float>>& normals , std::vector<std::vector<std::vector<float>>>& vertices , float r , float g , float b);
    void setVisible(bool visible);
    bool getVisible() const;
private:
    std::vector<Triangle> triangles;
    bool isVisible = true;

};

#endif // STL_OBJECT_H
