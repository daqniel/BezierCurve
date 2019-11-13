#include "Grid3D.h"

Grid3D::Grid3D()
{
	origin = glm::vec3(0);
	grid.negx = glm::vec3(-1, 0, 0);
	grid.posx = glm::vec3(1, 0, 0);
	grid.negy = glm::vec3(0, -1, 0);
	grid.posy = glm::vec3(0, 1, 0);
	grid.negz = glm::vec3(0, 0, -1);
	grid.posz = glm::vec3(0, 0, 1);
	
	m_interval = .1;

	m_scale = 2;
	
	generate();
	//could use geometry shader to create tick marks
}

void Grid3D::draw(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	s->use();
	s->setMatrix4f("model", glm::scale(glm::mat4(1.0), glm::vec3(m_scale)));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 6);
}

void Grid3D::generate()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*6, &grid, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
