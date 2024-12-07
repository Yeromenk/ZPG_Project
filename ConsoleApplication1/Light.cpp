
// Light.cpp
#include "Light.h"

Light::Light(const glm::vec3& color, float intensity)
    : color(color), intensity(intensity) {
}

void Light::setColor(const glm::vec3& color) {
    this->color = color;
    notify("light");
}

void Light::setIntensity(float intensity) {
    this->intensity = intensity;
    notify("light");
}

glm::vec3 Light::getColor() const {
    return color;
}

float Light::getIntensity() const {
    return intensity;
}