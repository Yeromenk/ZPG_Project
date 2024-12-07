#pragma once
#include <glm/vec3.hpp>

#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(const glm::vec3& direction,
        const glm::vec3& color,
        float intensity);

    void setDirection(const glm::vec3& direction);

    glm::vec3 getDirection() const override;

    int getType() const override; // Return an identifier for directional light, e.g., 1

private:
    glm::vec3 direction;
};


