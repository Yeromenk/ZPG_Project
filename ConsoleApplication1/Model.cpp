#include "Model.h"

Model::Model(ShaderProgram* shaderProgram, const float* points, int arraySize, int vertexCount, GLenum drawMode, const std::string& type, Material* material, Texture* texture)
	: DrawableObject(shaderProgram, type), drawMode(drawMode), vertexCount(vertexCount), material(material), texture(texture) {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, arraySize, points, GL_STATIC_DRAW);

	if (type == "skybox") {
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	}
	else {
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (texture ? 8 : 6) * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (texture ? 8 : 6) * sizeof(float), (void*)(3 * sizeof(float)));

		if (texture) {
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		}
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Model::Model(const char* path, ShaderProgram* shaderProgram, Material* material, Texture* texture, const std::string& type)
	: DrawableObject(shaderProgram, type), material(material), texture(texture)  {
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes
		| aiProcess_JoinIdenticalVertices
		| aiProcess_Triangulate
		| aiProcess_CalcTangentSpace;

	const aiScene* scene = importer.ReadFile(path, importOptions);
	std::vector<float> data;

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		exit(EXIT_FAILURE);
	}

	if (scene)
	{
		aiMesh* mesh = scene->mMeshes[0];
		vertexCount = mesh->mNumVertices * 3;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			for (unsigned int j = 0; j < 3; j++)
			{
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].y);
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].z);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].y);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].z);
				data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y);
			}
		}
	}
	drawMode = GL_TRIANGLES;

	this->VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	this->VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); //bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

}


Model::~Model() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Model::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	shader->use();

	if (type == "skybox")
	{
		glDepthFunc(GL_LEQUAL);
		shader->setMat4("viewMatrix", glm::mat4(glm::mat3(viewMatrix)));
		shader->setMat4("projectionMatrix", projectionMatrix);
		glDepthFunc(GL_LESS);
	}
	else
	{
		shader->setMat4("model", modelMatrix);
		shader->setMat4("viewMatrix", viewMatrix);
		shader->setMat4("projectionMatrix", projectionMatrix);
		shader->setVec3("material.ambient", material->getAmbient());
		shader->setVec3("material.diffuse", material->getDiffuse());
		shader->setVec3("material.specular", material->getSpecular());
	}

	applyTransformations(shader);

	if (texture)
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

	if (type == "skybox")
	{
		glDepthFunc(GL_LESS);
	}

	glUseProgram(0);
}

