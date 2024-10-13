#include "Model.h"


Model::Model() {}


Model::~Model() {
	glDeleteBuffers(1, &VBO_triangle);
	glDeleteVertexArrays(1, &VAO_triangle);
	glDeleteBuffers(1, &VBO_rectangle);
	glDeleteVertexArrays(1, &VAO_rectangle);
}

void Model::createTriangle() {
	float points[] = {
		-0.3f,  0.5f, 0.0f,
		 0.3f, -0.5f, 0.0f,
		-0.9f, -0.5f, 0.0f
	};

	// Create a vertex buffer object
	glGenBuffers(1, &VBO_triangle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// Create a vertex array object
	glGenVertexArrays(1, &VAO_triangle);
	glBindVertexArray(VAO_triangle);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_triangle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}


void Model::createRectangle() {
	float points[] = {
		-.5f, -.5f, .5f,  0, 0, 1,
		-.5f, .5f, .5f,  0, 0, 1,
	   .5f, .5f, .5f,  0, 0, 1,
	   .5f, -.5f, .5f,  0, 0, 1
	};

	glGenBuffers(1, &VBO_rectangle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_rectangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO_rectangle);
	glBindVertexArray(VAO_rectangle);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_rectangle); // ??

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

void Model::renderTriangle() {
	glBindVertexArray(VAO_triangle);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Model::renderRectangle() {
	glBindVertexArray(VAO_rectangle);
	glDrawArrays(GL_QUADS, 0, 4);
}

void Model::createTree() {
	glGenBuffers(1, &VBO_tree);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_tree);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO_tree);
	glBindVertexArray(VAO_tree);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_tree);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

void Model::renderTree() {
	glBindVertexArray(VAO_tree);
	glDrawArrays(GL_TRIANGLES, 0, 92814);
}
