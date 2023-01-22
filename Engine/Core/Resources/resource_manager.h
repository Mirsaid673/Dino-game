#pragma once

#include "Mesh/mesh.h"
#include "Mesh/mesh2d.h"
#include <vector>

class ResourceManager
{
public:
    static std::vector<Mesh> loadMesh(const char *file);

    static Mesh createCubeMesh(float x = 1.0f, float y = 1.0f, float z = 1.0f);
    static Mesh2d createQuadMesh(float x = 1.0f, float y = 1.0f);
    static Mesh2d createQuadMesh(const glm::vec2 &left_bottom, const glm::vec2 &right_top);
};