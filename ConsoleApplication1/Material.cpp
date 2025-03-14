#include "Material.h"

Material::Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
	: ambient(ambient), diffuse(diffuse), specular(specular) {
}

glm::vec3 Material::getAmbient() const {
	return ambient;
}

glm::vec3 Material::getDiffuse() const {
	return diffuse;
}

glm::vec3 Material::getSpecular() const {
	return specular;
}