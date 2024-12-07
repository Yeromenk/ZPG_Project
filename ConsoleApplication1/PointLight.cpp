#include "PointLight.h"

PointLight::PointLight(const glm::vec3& position,
    const glm::vec3& color,
    float intensity,
    float attenuation)
    : Light(color, intensity), position(position), attenuation(attenuation) {
}

void PointLight::setPosition(const glm::vec3& position) {
    this->position = position;
    notify("light");
}

void PointLight::setAttenuation(float attenuation) {
    this->attenuation = attenuation;
    notify("light");
}

glm::vec3 PointLight::getPosition() const {
    return position;
}

float PointLight::getAttenuation() const {
    return attenuation;
}

int PointLight::getType() const {
    return 0; // Identifier for point light
}