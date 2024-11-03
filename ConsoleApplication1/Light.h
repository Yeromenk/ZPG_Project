#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

#include "Subject.h"

class Light : public Subject {
public:
    Light(const glm::vec3& position, const glm::vec3& color, float intensity);

    void setPosition(const glm::vec3& position);
    void setColor(const glm::vec3& color);
    void setIntensity(float intensity);

    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;

    float getIntensity() const;

private:
    glm::vec3 position;
    glm::vec3 color;

    float intensity;
};

#endif 
