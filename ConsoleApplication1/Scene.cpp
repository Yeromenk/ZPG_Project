#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
    /*for (auto object : objects) {
        delete object;
    }
	for (auto light : lights) {
		delete light;
	}*/
}

void Scene::rotateTrees() {
	for (auto tree : rotatingTrees) {
        glm::vec3 axis(0.0f, 1.0f, 0.0f);
        tree->rotate(1.0f, axis);
	}
}

void Scene::translateBushes(float maxTranslation)
{
	for(auto bush : randomBushes)
	{
        bush->randomTranslate(maxTranslation);
	}
}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
    if(object->getType() == "tree")
    {
        rotatingTrees.push_back(object);
    }
	if (object->getType() == "bush")
	{
		randomBushes.push_back(object);
	}
 }

void Scene::draw(Camera* camera) {
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 projectionMatrix = camera->getProjectionMatrix(800.0f / 600.0f);

    for (auto object : objects) {
        glm::mat4 modelMatrix = object->getModelMatrix();
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

        ShaderProgram* shader = object->getShaderProgram();
        shader->use();
        shader->setMat4("modelMatrix", modelMatrix);
        shader->setMat4("viewMatrix", viewMatrix);
        shader->setMat4("projectionMatrix", projectionMatrix);
        shader->setMat3("normalMatrix", normalMatrix);
        shader->setVec3("materialDiffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader->setVec3("viewPos", camera->getPosition());
        object->draw(viewMatrix, projectionMatrix);

        glUseProgram(0);
    }

    if (!lights.empty()) {
        for (auto object : objects) {
            ShaderProgram* shader = object->getShaderProgram();
            shader->use();
            shader->setInt("numberOfLights", lights.size());
            for (int i = 0; i < lights.size(); i++) {
                shader->setLight("lights", *lights[i], i);
            }
            shader->setVec3("viewPos", camera->getPosition());

            glUseProgram(0);
        }
    }

}

void Scene::drawSkybox(Camera* camera)
{
    glDepthFunc(GL_LEQUAL);

	glm::mat4 viewMatrix = glm::mat4(glm::mat3(camera->getViewMatrix()));
	glm::mat4 projectionMatrix = camera->getProjectionMatrix(800.0f / 600.0f);

    for (auto object : objects) {
        if (object->getType() == "skybox") {
            ShaderProgram* shader = object->getShaderProgram();
            shader->use();
            shader->setMat4("view", viewMatrix);
            shader->setMat4("projection", projectionMatrix);
            shader->setInt("skybox", 1); // Ensure the uniform is set

            object->draw(viewMatrix, projectionMatrix);
        }
    }

	glDepthFunc(GL_LESS);
}


void Scene::setLight(Light* light) {
	lights.push_back(light);
}