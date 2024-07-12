#include "STLObject.h"
#include <fstream>
#include <iostream>
#include <sstream>

bool STLObject::loadSTL(const std::string& filename) 
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) 
    {
        std::cerr << "Error opening STL file." << std::endl;
        return false;
    }

    char header[80];
    file.read(header, sizeof(header));

    unsigned int numTriangles;
    file.read(reinterpret_cast<char*>(&numTriangles), sizeof(numTriangles));

    if (!file) 
    {
        std::cerr << "Error reading number of triangles." << std::endl;
        return false;
    }

    std::cout << "Number of triangles: " << numTriangles << std::endl;

    triangles.resize(numTriangles);
    for (unsigned int i = 0; i < numTriangles; ++i) 
    {
        file.read(reinterpret_cast<char*>(&triangles[i]), sizeof(Triangle));
        if (!file) 
        {
            std::cerr << "Error reading triangle " << i << std::endl;
            return false;
        }
        file.ignore(2); // Skip attribute byte count
    }

    return true;
}

void STLObject::renderObject(float r, float g, float b) const 
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    for (const auto& tri : triangles) 
    {
        glNormal3f(tri.normal.x, tri.normal.y, tri.normal.z);
        glVertex3f(tri.vertex1.x, tri.vertex1.y, tri.vertex1.z);
        glVertex3f(tri.vertex2.x, tri.vertex2.y, tri.vertex2.z);
        glVertex3f(tri.vertex3.x, tri.vertex3.y, tri.vertex3.z);
    }
    glEnd();
}

void STLObject::readASCIISTL(const std::string& filename, std::vector<std::vector<float>>& normals, std::vector<std::vector<std::vector<float>>>& vertices) 
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return;
    }

    std::string line;
    std::vector<float> normal(3);
    std::vector<std::vector<float>> triangleVertices(3, std::vector<float>(3));
    int vertexIndex = 0;

    while (std::getline(file, line)) 
    {
        std::istringstream ss(line);
        std::string word;
        ss >> word;

        if (word == "facet") 
        {
            ss >> word; 
            ss >> normal[0] >> normal[1] >> normal[2];
        }
        else if (word == "vertex") 
        {
            ss >> triangleVertices[vertexIndex][0] >> triangleVertices[vertexIndex][1] >> triangleVertices[vertexIndex][2];
            vertexIndex = (vertexIndex + 1) % 3;
            if (vertexIndex == 0) 
            {
                normals.push_back(normal);
                vertices.push_back(triangleVertices);
            }
        }
    }


    file.close();
}

void STLObject::renderByASCII(std::vector<std::vector<float>>& normals, std::vector<std::vector<std::vector<float>>>& vertices, float r, float g, float b)
{
    if (!isVisible) return;

    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b);
    for (size_t i = 0; i < normals.size(); ++i) 
    {
        glNormal3f(normals[i][0], normals[i][1], normals[i][2]);
        for (int j = 0; j < 3; ++j) 
        {
            //if (i == normals.size() / 2) std::cout << "x : " << vertices[i][j][0] << "  y : " << vertices[i][j][1] << "  z : " << vertices[i][j][2] << std::endl;
            glVertex3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
        }
    }
    glEnd();
}
void STLObject::setVisible(bool visible) {
    isVisible = visible;
}

bool STLObject::getVisible() const {
    return isVisible;
}

