#pragma once
#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const glm::vec3& position,
        const glm::vec3& color,
        float intensity,
        float attenuation);

    void setPosition(const glm::vec3& position);
    void setAttenuation(float attenuation);

    glm::vec3 getPosition() const override;
    float getAttenuation() const override;

    int getType() const override; // Return an identifier for point light, e.g., 0

private:
    glm::vec3 position;
    float attenuation;
};



