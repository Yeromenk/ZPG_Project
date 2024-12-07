// Light.h
#pragma once

#include "Subject.h"
#include <glm/glm.hpp>

class Light : public Subject {
public:
    Light(const glm::vec3& color, float intensity);
    virtual ~Light() = default;

    void setColor(const glm::vec3& color);
    void setIntensity(float intensity);

    glm::vec3 getColor() const;
    float getIntensity() const;

    // Optionally, make getType() pure virtual if needed
    virtual int getType() const = 0;


    // Add virtual methods with default implementations
    virtual glm::vec3 getPosition() const { return glm::vec3(0.0f); }
    virtual glm::vec3 getDirection() const { return glm::vec3(0.0f); }
    virtual float getAttenuation() const { return 0.0f; }
    virtual float getCutoff() const { return 0.0f; }


protected:
    glm::vec3 color;
    float intensity;
};

