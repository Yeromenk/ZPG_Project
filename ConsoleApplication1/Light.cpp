#include "Light.h"

Light::Light(const glm::vec3& position, const glm::vec3& color, float intensity)
    : position(position), color(color), intensity(intensity) {}

void Light::setPosition(const glm::vec3& position) {
    this->position = position;
    notify("light");
}

void Light::setColor(const glm::vec3& color) {
    this->color = color;
	notify("light");
}

void Light::setIntensity(float intensity) {
    this->intensity = intensity;
	notify("light");
}

glm::vec3 Light::getPosition() const {
    return position;
}

glm::vec3 Light::getColor() const {
    return color;
}

float Light::getIntensity() const {
    return intensity;
}
