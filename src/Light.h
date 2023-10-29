#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"
class Light
{
public:
	static unsigned int NUM_LIGHTS;
	Light(glm::vec3 pos, glm::vec3 intensity, glm::vec3 ambient)
	{
		this->pos = pos;
		this->intensity = intensity;
		this->ambient = ambient;
		this->index = NUM_LIGHTS++;
	}

	void set(Shader* s)
	{
		s->setVect3f("lights[" + std::to_string(index) + "].intensity", intensity);
		s->setVect3f("lights[" + std::to_string(index) + "].ambient", ambient);
		s->setVect3f("lights[" + std::to_string(index) + "].pos", pos);
	}
private:

	glm::vec3 pos;
	glm::vec3 intensity;
	glm::vec3 ambient;

	int index;
};

