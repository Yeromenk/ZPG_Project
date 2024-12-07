#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& direction,
    const glm::vec3& color,
    float intensity)
    : Light(color, intensity), direction(glm::normalize(direction)) {
}

void DirectionalLight::setDirection(const glm::vec3& direction) {
    this->direction = glm::normalize(direction);
    notify("light");
}

glm::vec3 DirectionalLight::getDirection() const {
    return direction;
}

int DirectionalLight::getType() const {
    return 1; // Identifier for directional light
}