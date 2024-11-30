#pragma once
#include "Renderer.h"

struct Wall
{
    glm::vec3 f_normal;
    float f_surface;

    Wall():
    f_normal(glm::vec3(0.f)),
    f_surface(0.f)
    {}

    Wall(
        const glm::vec3& normal,
        float surface
    ):
    f_normal(normal),
    f_surface(surface)
    {}

    bool pointInside(const glm::vec3& point) const {
        return glm::dot(point, f_normal) <= f_surface;
    }

    unsigned pointInside(const std::vector<glm::vec3>& points) const {
        unsigned maxDistInsideId = -1;
        unsigned id = 0;
        float maxDistInside = 0.f;
        for (const auto point: points) {
            float distInside = f_surface - glm::dot(point, f_normal);
            if (maxDistInside <= distInside) {
                maxDistInside = distInside;
                maxDistInsideId = id;
            }
            id++;
        }
        return maxDistInsideId;
    }
};
