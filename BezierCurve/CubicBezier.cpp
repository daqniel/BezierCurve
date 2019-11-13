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
	m_controlpoints[0] = c0;
	m_controlpoints[1] = c1;
	m_controlpoints[2] = c2;
	m_controlpoints[3] = c3;

	generate();
}

glm::vec4 CubicBezier::evaluate(float t)
{
	float s = 1 - t;
	for(int i = 0; i < 3; i++)
	{
		m_level1[i] = m_controlpoints[i]*s + m_controlpoints[i+1]*t;
	}

	for(int i = 0; i < 2; i++)
	{
		m_level2[i] = m_level1[i]*s + m_level1[i+1]*t;
	}

	m_eval_point = glm::vec4(m_level2[0] * s + m_level2[1] * t, t);

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

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, points.size());
	
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
	glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(float)*4, points.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
