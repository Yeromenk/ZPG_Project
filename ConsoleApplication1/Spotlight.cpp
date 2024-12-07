#include "Spotlight.h"

Spotlight::Spotlight(Camera* camera,
    const glm::vec3& color,
    float intensity,
    float attenuation,
    float cutoff)
    : PointLight(camera->getPosition(), color, intensity, attenuation),
    camera(camera),
    direction(camera->getDirection()),
    cutoff(cutoff) {
}

void Spotlight::update() {
    setPosition(camera->getPosition());
    setDirection(camera->getDirection());
}

void Spotlight::setCutoff(float cutoff) {
    this->cutoff = cutoff;
    notify("light");
}

float Spotlight::getCutoff() const {
    return cutoff;
}

void Spotlight::setDirection(const glm::vec3& direction) {
    this->direction = direction;
    notify("light");
}

glm::vec3 Spotlight::getDirection() const {
    return direction;
}

int Spotlight::getType() const {
    return 2; // Identifier for spotlight
}