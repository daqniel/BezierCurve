#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glad41/glad.h>
#include <vector>
#include "CubicBezier.h"
#include <iostream>
#include "Shader.h"

#include "Globals.h"


class CubicBezierPatch
{
public:
	CubicBezierPatch();
	~CubicBezierPatch();

	void draw(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawControlNet(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawControlNormals(Shader* s, glm::mat4 view, glm::mat4 projection);
	void generate(float interval);

private:
	struct Vertex
	{
		glm::vec4 pos;
		glm::vec3 norm;
		Vertex(glm::vec3 pos, float curvature)
		{
			this->pos = glm::vec4(pos.x, pos.y, pos.z, curvature);
			norm = glm::normalize(pos);
		}
	};
	std::vector<Vertex> controlNet;
	GLuint controlNetVAO, controlNetVBO;
};

