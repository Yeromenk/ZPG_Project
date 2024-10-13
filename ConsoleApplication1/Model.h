#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include "Models/tree.h"


class Model {
public:
    Model();
    ~Model();

    void createTriangle();
    void createRectangle();
	void createTree();

    void renderTriangle();
    void renderRectangle();
	void renderTree();
    
private:
    GLuint VAO_triangle, VBO_triangle;
    GLuint VAO_rectangle, VBO_rectangle;
	GLuint VAO_tree, VBO_tree;
};

#endif