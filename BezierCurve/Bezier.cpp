#include "Bezier.h"

Bezier::Bezier()
{

	glGenVertexArrays(1, &controlVAO);
	glGenBuffers(1, &controlVBO);

	glGenVertexArrays(1, &polygonVAO);
	glGenBuffers(1, &polygonVBO);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glGenVertexArrays(1, &pointVAO);
	glGenBuffers(1, &pointVBO);

	glGenVertexArrays(1, &frenetVAO);
	glGenBuffers(1, &frenetVBO);

	m_interval = 0.01f;
	control_point_color = glm::vec4(1);

}

Bezier::~Bezier()
{
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &controlVBO);
	//glDeleteBuffers(1, &polygonVBO);

	//glDeleteVertexArrays(1, &VAO);
	//glDeleteVertexArrays(1, &controlVAO);
	//glDeleteVertexArrays(1, &polygonVAO);
}

void Bezier::setControlColor(glm::vec4 color)
{
	control_point_color = color;
}
/*
void Bezier::setControlPoints(glm::vec3 c0, glm::vec3 c1, glm::vec3 c2, glm::vec3 c3 = glm::vec3(0,0,0))
{
	m_controlpoints[0] = glm::vec4(c0, 0);
	m_controlpoints[1] = glm::vec4(c1, 0);
	m_controlpoints[2] = glm::vec4(c2, 0);
	m_controlpoints[3] = glm::vec4(c3, 0);

	generate();
}*/

// maybe implement this some day idk
void rotateControlPoints(float angle, glm::vec3 axis)
{
	//glm::mat4 model;
	//model = glm::translate()
	//model = glm::rotate(model, glm::radians(angle), axis);

}

//glm::vec4 Bezier::evaluate(float t)
//{
//	float s = 1 - t;
//	for (int i = 0; i < NUM_CONTROL_POINTS-1; i++)
//	{
//		m_level1[i] = glm::vec4(glm::vec3(m_controlpoints[i]) * s + glm::vec3(m_controlpoints[i + 1]) * t, 1);
//	}
//
//	for (int i = 0; i < NUM_CONTROL_POINTS-2; i++)
//	{
//		m_level2[i] = glm::vec4(glm::vec3(m_level1[i]) * s + glm::vec3(m_level1[i + 1] * t), 2);
//	}
//
//	m_eval_point = glm::vec4(glm::vec3(m_level2[0]) * s + glm::vec3(m_level2[1]) * t, t);
//
//	// MAYBE CHANGE CLASS STRUCTURE, PROBABLY WANT TO STORE MULTIPLE SAMPLES OF EVALUATION.
//	// OR, have it evaluate in constructor and store all the points we need to display, use geometry shader for showing steps?
//	return m_eval_point;
//}

void Bezier::draw(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	s->use();
	s->setMatrix4f("model", glm::mat4(1.0));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);

	s->setFloat("evalpoint_time", m_eval_point.w);

	glBindVertexArray(VAO);


	glDrawArrays(GL_LINE_STRIP, 0, points.size());

}

void Bezier::drawEvalPoint(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	s->use();
	s->setMatrix4f("model", glm::mat4(1.0));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);
	s->setVect3f("control_color", glm::vec3(0));
	glBindVertexArray(pointVAO);

	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, &m_eval_point, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_POINTS, 0, 1);
}

//void Bezier::drawControlPoints(Shader* s, glm::mat4 view, glm::mat4 projection)
//{
//
//	s->use();
//	s->setMatrix4f("model", glm::mat4(1.0));
//	s->setMatrix4f("view", view);
//	s->setMatrix4f("projection", projection);
//	s->setVect3f("control_color", control_point_color);
//
//	glBindVertexArray(controlVAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, controlVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * NUM_CONTROL_POINTS, &m_controlpoints, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glDrawArrays(GL_POINTS, 0, 4);
//}

/*void Bezier::drawControlPolygon(Shader* s, glm::mat4 view, glm::mat4 projection, int evalLevel)
{
	s->use();
	s->setMatrix4f("model", glm::mat4(1.0));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);
	s->setFloat("eval_level", evalLevel);
	s->setVect3f("control_color", control_point_color);

	glBindVertexArray(polygonVAO);

	glBindBuffer(GL_ARRAY_BUFFER, polygonVBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 4, m_controlpoints, GL_STATIC_DRAW);
	glDrawArrays(GL_LINE_STRIP, 0, 4);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 3, m_level1, GL_STATIC_DRAW);
	glDrawArrays(GL_LINE_STRIP, 0, 3);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 2, m_level2, GL_STATIC_DRAW);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
}*/

void Bezier::drawFrenetFrame(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	glm::vec4 empty;

	//probably need to parametrize to arclength or some shit idk
	glm::vec4 prev_point;
	glm::vec4 prev_prev_point;
	glm::vec4 next_point;
	glm::vec4 next_next_point;
	for (int i = 0; i < points.size() - 1; i++)
	{
		if (i > 1)
		{
			prev_prev_point = points[i - 2];
			prev_point = points[i - 1];
		}

		if (points[i].w > m_eval_point.w)
		{

			next_point = points[i];
			next_next_point = points[i + 1];
			break;
		}
	}
	glm::vec4 eval_point = m_eval_point;

	if (next_point == empty)
	{
		next_next_point = eval_point;
		next_point = prev_point;
		eval_point = prev_prev_point;
	}

	glm::vec3 gradient = glm::normalize(glm::vec3(next_point - eval_point));
	glm::vec3 gradient2 = glm::normalize(glm::vec3(next_next_point - next_point));
	glm::vec3 gradientofgradient = glm::normalize(gradient2 - gradient);

	glm::vec3 tangent = gradient;
	glm::vec3 normal = gradientofgradient;
	glm::vec3 binormal = glm::cross(tangent, normal);

	// use uniform buffer block thing maybe 
	//FrenetFrame frame;
	//frame.tangent = tangent;
	//frame.normal = normal;
	//frame.binormal = binormal;

	s->use();
	s->setMatrix4f("model", glm::mat4(1.0));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);

	s->setVect3f("tangent", tangent);
	s->setVect3f("normal", normal);
	s->setVect3f("binormal", binormal);

	s->setVect3f("control_color", control_point_color);

	//probably need to paramatrize to arclength or something

	glBindVertexArray(frenetVAO);

	glBindBuffer(GL_ARRAY_BUFFER, frenetVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, &m_eval_point, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_POINTS, 0, 1);

}


void Bezier::generate()
{
	points.clear();

	for (float t = 0.0f; t <= 1.0001f; t += m_interval)
	{
		points.push_back(evaluate(t));
	}
	evaluate(0);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float) * 4, points.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
#include "Bezier.h"
