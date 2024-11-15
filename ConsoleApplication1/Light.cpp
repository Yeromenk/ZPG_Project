#include "Light.h"

Light::Light(const glm::vec3& position, const glm::vec3& color, float intensity, float attenuation)
    : position(position), color(color), intensity(intensity), attenuation(attenuation) {}

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

void Light::setAttenuation(float attenuation) {
	this->attenuation = attenuation;
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

float Light::getAttenuation() const {
	return attenuation;
}
