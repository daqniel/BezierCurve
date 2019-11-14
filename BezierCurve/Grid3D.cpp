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

	m_scale = 1;
	m_tick_precision = 1;
	
	generate();
	generateTicks(m_tick_precision);
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

void Grid3D::drawticks(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	s->use();
	s->setMatrix4f("model", glm::scale(glm::mat4(1.0), glm::vec3(m_scale)));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);

	glBindVertexArray(tickVAO);
	glDrawArrays(GL_POINTS, 0, m_numticks);
}

void Grid3D::drawticklines(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	s->use();
	s->setMatrix4f("model", glm::scale(glm::mat4(1.0), glm::vec3(m_scale)));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);

	s->setVect3f("pos", glm::vec3(grid.posx.x, grid.posy.y, grid.posz.z));
	s->setVect3f("neg", glm::vec3(grid.negx.x, grid.negy.y, grid.negz.z));

	glBindVertexArray(tickVAO);
	glDrawArrays(GL_POINTS, 0, m_numticks);
}


void Grid3D::setGridBoundaries(glm::vec3 pos, glm::vec3 neg)
{
	grid.negx = glm::vec3(neg.x, 0, 0);
	grid.posx = glm::vec3(pos.x, 0, 0);
	grid.negy = glm::vec3(0, neg.y, 0);
	grid.posy = glm::vec3(0, pos.y, 0);
	grid.negz = glm::vec3(0, 0, neg.z);
	grid.posz = glm::vec3(0, 0, pos.z);

	generate();
	generateTicks(m_tick_precision);
}

void Grid3D::setTickPrecision(float precision)
{
	m_tick_precision = precision;
	generateTicks(precision);
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

void Grid3D::generateTicks(float precision)
{
	tickpoints.clear();
	glm::vec3 xdir = grid.posx - grid.negx;
	int numticks = int(glm::length(xdir) / precision);
	xdir = glm::normalize(xdir);
	for (int i = 0; i <= numticks; i++)
	{
		glm::vec3 point = grid.negx + precision * i * xdir;
		tickpoints.push_back(point);
	}
	glm::vec3 ydir = grid.posy - grid.negy;
	numticks = int(glm::length(ydir) / precision);
	ydir = glm::normalize(ydir);
	for (int i = 0; i <= numticks; i++)
	{
		glm::vec3 point = grid.negy + precision * i * ydir;
		tickpoints.push_back(point);
	}
	glm::vec3 zdir = grid.posz - grid.negz;
	numticks = int(glm::length(zdir) / precision);
	zdir = glm::normalize(zdir);
	for (int i = 0; i <= numticks; i++)
	{
		glm::vec3 point = grid.negz + precision * i * zdir;
		tickpoints.push_back(point);
	}

	m_numticks = tickpoints.size();
	glGenVertexArrays(1, &tickVAO);
	glGenBuffers(1, &tickVBO);
	glBindVertexArray(tickVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tickVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*m_numticks, tickpoints.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}
