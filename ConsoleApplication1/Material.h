#pragma once
#include <glm/vec3.hpp>

class Material
{
public:
	Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

	glm::vec3 getAmbient() const;
	glm::vec3 getDiffuse() const;
	glm::vec3 getSpecular() const;

private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

