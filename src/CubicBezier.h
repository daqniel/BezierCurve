#ifndef _CUBIC_BEZIER_H_
#define _CUBIC_BEZIER_H_
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

class CubicBezier
{
public:

	CubicBezier();
	~CubicBezier();

	// define control points and shading color for curve
	void setControlPoints(glm::vec3 c0, glm::vec3 c1, glm::vec3 c2, glm::vec3 c3);
	void setControlColor(glm::vec4 color);

	// evaluate the curve at t
	glm::vec4 evaluate(float t);

	// functions for evaluating, buffering, and drawing the cubic bezier curve and derivative structures
	void draw(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawEvalPoint(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawControlPoints(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawControlPolygon(Shader* s, glm::mat4 view, glm::mat4 projection, int evalLevel);
	void drawFrenetFrame(Shader* s, glm::mat4 view, glm::mat4 projection);

private:

	// Generate list of points, bind and buffer vertex data
	void generate();

	// defined control points and evaluated subdivided lower order control points
	glm::vec4 m_controlpoints[4];
	glm::vec4 m_level1[3];
	glm::vec4 m_level2[2];

	glm::vec3 control_point_color;

	// defines the resolution at which we evaluate the bezier curve and store points
	float m_interval;

	// evaluated data for bezier curve
	std::vector<glm::vec4> points;
	glm::vec4 m_eval_point;

	// VAO and VBO handles for bezier curve and derivative structures
	GLuint VAO, VBO;
	GLuint controlVAO, controlVBO;
	GLuint polygonVAO, polygonVBO;
	GLuint pointVAO, pointVBO;
	GLuint frenetVAO, frenetVBO;
};
#endif