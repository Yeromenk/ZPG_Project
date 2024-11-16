#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

#include "Subject.h"

class Light : public Subject {
public:
    Light(int type, const glm::vec3& position, const glm::vec3 direction ,const glm::vec3& color, float intensity, float attenuation, float cutoff);

	int getType() const;

    void setPosition(const glm::vec3& position);
    void setColor(const glm::vec3& color);
    void setIntensity(float intensity);
    void setAttenuation(float attenuation);
	void setDirection(const glm::vec3& direction);

    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;
    glm::vec3 getDirection() const;

    float getIntensity() const;
	float getAttenuation() const;
	float getCutoff() const;

private:
    int type;
    glm::vec3 position;
	glm::vec3 direction;
    glm::vec3 color;

    float intensity;
	float attenuation;
    float cutoff;
};

#endif 
