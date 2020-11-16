#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "glad.h"
#include <glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/fwd.hpp>

struct coordPair {
    float x, y;
};

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Color;
};
#endif // !GRAPHICS_H
