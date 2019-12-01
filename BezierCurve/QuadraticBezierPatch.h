#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "QuadraticBezier.h"
#include <iostream>
#include "Shader.h"

class QuadraticBezierPatch
{
public:
	QuadraticBezierPatch();
	~QuadraticBezierPatch();

	void draw(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawControlNet(Shader* s, glm::mat4 view, glm::mat4 projection);
	void generate(float interval);

private:
	std::vector<glm::vec4> points;
	std::vector<glm::vec4> controlNet;
	GLuint triangleVAO, triangleVBO;
	GLuint controlNetVAO, controlNetVBO;
};

