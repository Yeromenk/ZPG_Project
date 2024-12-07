#pragma once
#include "PointLight.h"
#include "Camera.h"

class Spotlight : public PointLight {
public:
    Spotlight(Camera* camera,
        const glm::vec3& color,
        float intensity,
        float attenuation,
        float cutoff);

    void update();

    void setCutoff(float cutoff);
    float getCutoff() const override;

    void setDirection(const glm::vec3& direction);
    glm::vec3 getDirection() const override;

    int getType() const override;

private:
    Camera* camera;
    glm::vec3 direction;
    float cutoff;
};


