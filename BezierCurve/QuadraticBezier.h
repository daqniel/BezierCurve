#ifndef _QUADRATIC_BEZIER_H_
#define _QUADRATIC_BEZIER_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"

#ifndef _FRENETFRAME_H_
#define _FRENETFRAME_H_
struct FrenetFrame
{
	glm::vec3 tangent;
	glm::vec3 normal;
	glm::vec3 binormal;
};
#endif

class QuadraticBezier
{
public:

	QuadraticBezier();
	~QuadraticBezier();

	void setControlColor(glm::vec4 color);
	void setInterval(float i) {
		m_interval = i;
	}
	void setControlPoints(glm::vec3 c0, glm::vec3 c1, glm::vec3 c2);

	std::vector<glm::vec4> getPoints() { return points; }

	const glm::vec4* getControlPoints() { return m_controlpoints; }

	glm::vec4 evaluate(float t);

	void draw(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawEvalPoint(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawControlPoints(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawControlPolygon(Shader* s, glm::mat4 view, glm::mat4 projection, int evalLevel);
	void drawFrenetFrame(Shader* s, glm::mat4 view, glm::mat4 projection);

private:

	void generate();
	glm::vec4 m_controlpoints[3];
	glm::vec4 m_level1[2];

	glm::vec3 control_point_color;

	float m_interval;
	std::vector<glm::vec4> points;

	glm::vec4 m_eval_point;

	GLuint VAO, VBO;

	GLuint controlVAO, controlVBO;

	GLuint polygonVAO, polygonVBO;

	GLuint pointVAO, pointVBO;

	GLuint frenetVAO, frenetVBO;
};



#endif