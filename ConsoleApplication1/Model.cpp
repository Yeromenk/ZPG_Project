#include "Model.h"

Model::Model(ShaderProgram* shaderProgram, const float* points, int arraySize, int vertexCount, GLenum drawMode, const std::string& type, Material* material, Texture* texture, bool isSkyBox)
    : DrawableObject(shaderProgram, type), drawMode(drawMode), vertexCount(vertexCount), material(material), texture(texture), isSkyBox(isSkyBox) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, arraySize, points, GL_STATIC_DRAW);

    if (isSkyBox) {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    }
    else { 
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (texture ? 8 : 6) * sizeof(float), (void*)0);

        
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (texture ? 8 : 6) * sizeof(float), (void*)(3 * sizeof(float)));

        if (texture) {
           
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        }
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Model::~Model() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Model::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    shader->use();

    if (isSkyBox)
    {
        glDepthFunc(GL_LEQUAL);
		shader->setMat4("viewMatrix", glm::mat4(glm::mat3(viewMatrix)));
		shader->setMat4("projectionMatrix", projectionMatrix);
    } else
    {
        shader->setMat4("model", modelMatrix);
        shader->setMat4("viewMatrix", viewMatrix);
        shader->setMat4("projectionMatrix", projectionMatrix);
        shader->setVec3("material.ambient", material->getAmbient());
        shader->setVec3("material.diffuse", material->getDiffuse());
        shader->setVec3("material.specular", material->getSpecular());
    }
    
    applyTransformations(shader);

    if(texture)
    {
		texture->bind(0);
		shader->setInt("textureUnitID", 0);
    }

    glBindVertexArray(VAO);
    glDrawArrays(drawMode, 0, vertexCount);
    glBindVertexArray(0);

	if (texture)
	{
		texture->unbind();
	}

	if (isSkyBox)
	{
		glDepthFunc(GL_LESS);
	}

	glUseProgram(0);
}

