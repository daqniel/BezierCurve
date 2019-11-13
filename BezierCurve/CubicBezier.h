#ifndef _CUBIC_BEZIER_H_
#define _CUBIC_BEZIER_H_
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

class CubicBezier
{
public:

	CubicBezier();
	~CubicBezier();

	void setControlPoints(glm::vec3 c0, glm::vec3 c1, glm::vec3 c2, glm::vec3 c3);

	glm::vec4 evaluate(float t);

	void draw(Shader* s, glm::mat4 view, glm::mat4 projection);
private:

	void generate();
	glm::vec3 m_controlpoints[4];
	glm::vec3 m_level1[3];
	glm::vec3 m_level2[2];

	float m_interval;
	std::vector<glm::vec4> points;

	glm::vec4 m_eval_point;

	GLuint VAO, VBO;
};

#endif