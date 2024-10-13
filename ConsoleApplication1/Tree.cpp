//#include "Tree.h"
//#include "tree.h"
//
//Tree::Tree() : position(0.0f, 0.0f, 0.0f) {}
//
//Tree::~Tree() {
//	glDeleteBuffers(1, &VBO_tree);
//	glDeleteVertexArrays(1, &VAO_tree);
//}
//
//void Tree::createTree() {
//    glGenBuffers(1, &VBO_tree);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_tree);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);
//
//    glGenVertexArrays(1, &VAO_tree);
//    glBindVertexArray(VAO_tree);
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_tree);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//}
//
////void Tree::renderTree()
////{
////	glBindVertexArray(VAO_tree);
////	glDrawArrays(GL_TRIANGLES, 0, 92814);
////}
//
//void Tree::setPosition(const glm::vec3& position)
//{
//	this->position = position;
//}
//
//glm::vec3 Tree::getPosition() const
//{
//	return position;
//}