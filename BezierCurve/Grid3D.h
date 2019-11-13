#ifndef _GRID3D_H_
#define _GRID3D_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
struct GridData
{
	glm::vec3 negx, posx;
	glm::vec3 negy, posy;
	glm::vec3 negz, posz;
};

class Grid3D
{
public:
	Grid3D();

	void draw(Shader* s, glm::mat4 view, glm::mat4 projection);
private:

	void generate();

	float m_interval;
	float m_scale;

	glm::vec3 origin;
	GridData grid;

	GLuint VAO;
	GLuint VBO;
};

#endif // !_GRID3D_H_
