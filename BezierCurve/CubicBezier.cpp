#include "CubicBezier.h"

CubicBezier::CubicBezier()
{
	m_interval = 0.01f;
	setControlPoints(glm::vec3(-1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0), glm::vec3(2, 0, 0));
}

CubicBezier::~CubicBezier()
{

}


void CubicBezier::setControlPoints(glm::vec3 c0, glm::vec3 c1, glm::vec3 c2, glm::vec3 c3)
{
	m_controlpoints[0] = glm::vec4(c0, 1);
	m_controlpoints[1] = glm::vec4(c1, 2);
	m_controlpoints[2] = glm::vec4(c2, 4);
	m_controlpoints[3] = glm::vec4(c3, 8);

	glGenVertexArrays(1, &controlVAO);
	glGenBuffers(1, &controlVBO);
	glBindVertexArray(controlVAO);

	glBindBuffer(GL_ARRAY_BUFFER, controlVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 4, &m_controlpoints, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_POINTS, 0, 1);

	generate();
}

glm::vec4 CubicBezier::evaluate(float t)
{
	float s = 1 - t;
	for (int i = 0; i < 3; i++)
	{
		m_level1[i] = glm::vec4(glm::vec3(m_controlpoints[i]) * s + glm::vec3(m_controlpoints[i + 1]) * t, t);
	}

	for (int i = 0; i < 2; i++)
	{
		m_level2[i] = glm::vec4(glm::vec3(m_level1[i]) * s + glm::vec3(m_level1[i + 1] * t), t);
	}

	m_eval_point = glm::vec4(glm::vec3(m_level2[0]) * s + glm::vec3(m_level2[1]) * t, t);

	// MAYBE CHANGE CLASS STRUCTURE, PROBABLY WANT TO STORE MULTIPLE SAMPLES OF EVALUATION.
	// OR, have it evaluate in constructor and store all the points we need to display, use geometry shader for showing steps?
	return m_eval_point;
}

void CubicBezier::draw(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	s->use();
	s->setMatrix4f("model", glm::mat4(1.0));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);

	s->setFloat("evalpoint_time", m_eval_point.w);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, points.size());

}

void CubicBezier::drawEvalPoint(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	s->use();
	s->setMatrix4f("model", glm::mat4(1.0));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);

	GLuint pointVAO, pointVBO;
	glGenVertexArrays(1, &pointVAO);
	glGenBuffers(1, &pointVBO);
	glBindVertexArray(pointVAO);

	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, &m_eval_point, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_POINTS, 0, 1);
}

void CubicBezier::drawControlPoints(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	s->use();
	s->setMatrix4f("model", glm::mat4(1.0));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);
	s->setVect3f("control_color", control_point_color);

	glBindVertexArray(controlVAO);
	glDrawArrays(GL_POINTS, 0, 4);
}


void CubicBezier::generate()
{
	points.clear();

	for (float t = 0.0f; t <= 1.0001f; t += m_interval)
	{
		points.push_back(evaluate(t));
	}
	evaluate(0);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float) * 4, points.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
