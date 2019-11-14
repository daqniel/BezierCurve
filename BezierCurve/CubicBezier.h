#ifndef _CUBIC_BEZIER_H_
#define _CUBIC_BEZIER_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"

class CubicBezier
{
public:

	CubicBezier();
	~CubicBezier();

	void setControlColor(glm::vec4 color);

	void setControlPoints(glm::vec3 c0, glm::vec3 c1, glm::vec3 c2, glm::vec3 c3);

	glm::vec4 evaluate(float t);

	void draw(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawEvalPoint(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawControlPoints(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawControlPolygon(Shader* s, glm::mat4 view, glm::mat4 projection, int evalLevel);
private:

	void generate();
	glm::vec4 m_controlpoints[4];
	glm::vec4 m_level1[3];
	glm::vec4 m_level2[2];

	glm::vec3 control_point_color;

	float m_interval;
	std::vector<glm::vec4> points;

	glm::vec4 m_eval_point;

	GLuint VAO, VBO;

	GLuint controlVAO, controlVBO;

	GLuint polygonVAO, polygonVBO;

	GLuint pointVAO, pointVBO;
};


#endif